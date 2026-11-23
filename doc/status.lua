-- status.lua
-- Shows which Cairo functions are bound by Moon Over Cairo.
--
-- The Cairo prototypes come from the Cairo headers. What is bound comes from parsing src/moc.c:
-- a Cairo function cairo_<name> counts as covered when
--   1. "<name>" is registered in the luaL_Reg table of luaopen_moc (commented-out entries do not count), and
--   2. the C function registered for it really calls cairo_<name>.
-- A function that is registered but does not call its Cairo counterpart is shown in red with a note.
--
-- Usage: lua doc/status.lua [path/to/cairo/src/]

local CairoPath_s   = arg[1] or '/Users/marcotrosi/Code/clones/cairo/src/'
local HeaderFiles_t = { 'cairo.h', 'cairo-svg.h', 'cairo-pdf.h', 'cairo-ps.h' }

-- src/moc.c is found relative to this script, so it can be run from any directory
local ScriptDir_s = (arg[0]:match('^(.*)/[^/]*$') or '.') .. '/'
local MocFile_s   = ScriptDir_s .. '../src/moc.c'

local GREEN = '\27[32m'
local RED   = '\27[31m'
local BOLD  = '\27[1m'
local RESET = '\27[0m'

local function readFile(path)
   local f, err = io.open(path, 'r')
   if not f then
      io.stderr:write('error: cannot open ' .. path .. ' (' .. tostring(err) .. ')\n')
      os.exit(1)
   end
   local s = f:read('a')
   f:close()
   return s
end

-- Returns a list of { name = 'cairo_xyz', proto = 'void cairo_xyz (...);' } in header order
local function parseHeader(path)
   local result  = {}
   local collect = false
   local proto   = ''
   for line in (readFile(path) .. '\n'):gmatch('(.-)\r?\n') do
      if line:sub(1, 12) == 'cairo_public' then
         collect = true
         proto   = ''
      end
      if collect then
         proto = proto .. ' ' .. line
         if line:sub(-1) == ';' then
            collect = false
            proto = proto:gsub('cairo_public%s*', ''):gsub('%s+', ' '):gsub('^ ', '')
            local name = proto:match('([%w_]+)%s*%(')
            if name then
               table.insert(result, { name = name, proto = proto })
            end
         end
      end
   end
   return result
end

-- Returns a set of covered Cairo function names and a set of registered-but-wrong ones
local function parseMoc(path)
   local src = readFile(path)
   src = src:gsub('/%*.-%*/', ''):gsub('//[^\n]*', '')   -- strip comments

   -- registered Lua names and their C functions: {"name", cfunc},
   local reg_s = src:match('luaL_Reg%s+[%w_]+%s*%[%]%s*=%s*(%b{})') or ''
   local covered_t, wrong_t = {}, {}
   for luaname, cfunc in reg_s:gmatch('{%s*"([%w_]+)"%s*,%s*([%w_]+)%s*}') do
      -- body of the C function (balanced braces after its definition)
      local body = src:match('int%s+' .. cfunc .. '%s*%(%s*lua_State%s*%*%s*[%w_]+%s*%)%s*(%b{})') or ''
      local caironame = 'cairo_' .. luaname
      if body:find(caironame .. '%s*%(') then
         covered_t[caironame] = true
      else
         wrong_t[caironame] = true
      end
   end
   return covered_t, wrong_t
end

local covered_t, wrong_t = parseMoc(MocFile_s)
local total_n, covered_n = 0, 0

for _, header in ipairs(HeaderFiles_t) do
   local protos_t  = parseHeader(CairoPath_s .. header)
   local hcovered  = 0
   print(BOLD .. '== ' .. header .. ' ==' .. RESET)
   for _, p in ipairs(protos_t) do
      if covered_t[p.name] then
         hcovered = hcovered + 1
         print(GREEN .. '  [x] ' .. p.proto .. RESET)
      elseif wrong_t[p.name] then
         print(RED .. '  [!] ' .. p.proto .. '   <-- registered, but does not call ' .. p.name .. RESET)
      else
         print(RED .. '  [ ] ' .. p.proto .. RESET)
      end
   end
   print(string.format('%s%d/%d covered%s\n', BOLD, hcovered, #protos_t, RESET))
   total_n   = total_n + #protos_t
   covered_n = covered_n + hcovered
end

print(string.format('%sTotal: %s%d%s / %d covered (%.1f%%)%s',
   BOLD, GREEN, covered_n, RESET .. BOLD, total_n, total_n > 0 and 100 * covered_n / total_n or 0, RESET))
