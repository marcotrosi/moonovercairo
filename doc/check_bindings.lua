local CollectLine      = false
local CairoPath_s      = '/Users/marcotrosi/Code/clones/cairo/src/'
local HeaderFile_s     = 'cairo.h'
local HeaderFile_t     = readf(CairoPath_s .. HeaderFile_s)
local SVGHeaderFile_s  = 'cairo-svg.h'
local SVGHeaderFile_t  = readf(CairoPath_s .. SVGHeaderFile_s)
local PDFHeaderFile_s  = 'cairo-pdf.h'
local PDFHeaderFile_t  = readf(CairoPath_s .. PDFHeaderFile_s)
local PSHeaderFile_s   = 'cairo-ps.h'
local PSHeaderFile_t   = readf(CairoPath_s .. PSHeaderFile_s)
local FuncPrototype_s  = ''
local FuncPrototypes_t = {}

function parseHeader(t)
   for i,l in ipairs(t) do

      if string.sub(l, 0,12) == 'cairo_public' then
         CollectLine = true
         FuncPrototype_s = ''
      end

      if CollectLine then
         FuncPrototype_s = FuncPrototype_s .. ' ' .. l

         if string.sub(l, -1) == ';' then
            CollectLine = false
            FuncPrototype_s = string.gsub(FuncPrototype_s, 'cairo_public%s*', ''):gsub('%s+', ' ')
            FuncPrototypes_t[FuncPrototype_s] = false
            -- table.insert(FuncPrototypes_t, FuncPrototype_s)
         end
      end
   end
end

parseHeader(HeaderFile_t)
parseHeader(SVGHeaderFile_t)
parseHeader(PDFHeaderFile_t)
parseHeader(PSHeaderFile_t)

-- for _,p in ipairs(FuncPrototypes_t) do
--    print(p)
-- end

-- printt(FuncPrototypes_t, 'doc/binding_status2.lua')
