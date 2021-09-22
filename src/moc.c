#include <cairo.h>
#include <cairo-svg.h>
#include <cairo-pdf.h>
#include <cairo-ps.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "moc.h"

// functions <<<
static void dump(lua_State *L) // <<<
{
   int top=lua_gettop(L);
   for (int i=1; i <= top; i++)
   {
      printf("%d\t%s\t", i, luaL_typename(L,i));
      switch (lua_type(L, i))
      {
         case LUA_TNUMBER:
            printf("%g\n",lua_tonumber(L,i));
            break;
         case LUA_TSTRING:
            printf("%s\n",lua_tostring(L,i));
            break;
         case LUA_TBOOLEAN:
            printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
            break;
         case LUA_TNIL:
            printf("%s\n", "nil");
            break;
         default:
            printf("%p\n",lua_topointer(L,i));
            break;
      }
   }
} // >>>

int luaopen_moc(lua_State *L) // <<<
{
   const luaL_Reg Functions[] =
   {
      {"arc", arc},
      {"arc_negative", arc_negative},
      {"close_path", close_path},
      {"create", create},
      {"curve_to", curve_to},
      {"destroy", destroy},
      {"fill", fill},
      {"image_surface_create", image_surface_create},
      {"line_to", line_to},
      {"move_to", move_to},
      {"new_path", new_path},
      {"new_sub_path", new_sub_path},
      {"rectangle", rectangle},
      {"rel_curve_to", rel_curve_to},
      {"rel_line_to", rel_line_to},
      {"rel_move_to", rel_move_to},
      {"restore", restore},
      {"rotate", rotate},
      {"save", save},
      {"scale", scale},
      {"set_antialias", set_antialias},
      {"set_line_cap", set_line_cap},
      {"set_line_join", set_line_join},
      {"set_line_width", set_line_width},
      {"set_source_rgb", set_source_rgb},
      {"set_source_rgba", set_source_rgba},
      {"stroke", stroke},
      {"surface_destroy", surface_destroy},
      {"surface_write_to_png", surface_write_to_png},
      {"svg_surface_create", svg_surface_create},
      {"pdf_surface_create", pdf_surface_create},
      {"ps_surface_create", ps_surface_create},
      {"translate", translate},
      {NULL, NULL}
   };

   luaL_newlib(L, Functions);

   REGISTER_ENUM("ANTIALIAS_DEFAULT" , CAIRO_ANTIALIAS_DEFAULT ) 
   REGISTER_ENUM("ANTIALIAS_NONE"    , CAIRO_ANTIALIAS_NONE    ) 
   REGISTER_ENUM("ANTIALIAS_GRAY"    , CAIRO_ANTIALIAS_GRAY    ) 
   REGISTER_ENUM("ANTIALIAS_SUBPIXEL", CAIRO_ANTIALIAS_SUBPIXEL) 
   REGISTER_ENUM("ANTIALIAS_FAST"    , CAIRO_ANTIALIAS_FAST    ) 
   REGISTER_ENUM("ANTIALIAS_GOOD"    , CAIRO_ANTIALIAS_GOOD    ) 
   REGISTER_ENUM("ANTIALIAS_BEST"    , CAIRO_ANTIALIAS_BEST    ) 

   REGISTER_ENUM("LINE_CAP_BUTT"  , CAIRO_LINE_CAP_BUTT  ) 
   REGISTER_ENUM("LINE_CAP_ROUND" , CAIRO_LINE_CAP_ROUND ) 
   REGISTER_ENUM("LINE_CAP_SQUARE", CAIRO_LINE_CAP_SQUARE) 

   REGISTER_ENUM("LINE_JOIN_MITER", CAIRO_LINE_JOIN_MITER)
   REGISTER_ENUM("LINE_JOIN_ROUND", CAIRO_LINE_JOIN_ROUND)
   REGISTER_ENUM("LINE_JOIN_BEVEL", CAIRO_LINE_JOIN_BEVEL)

   REGISTER_ENUM("FORMAT_INVALID"  , CAIRO_FORMAT_INVALID  )
   REGISTER_ENUM("FORMAT_ARGB32"   , CAIRO_FORMAT_ARGB32   )
   REGISTER_ENUM("FORMAT_RGB24"    , CAIRO_FORMAT_RGB24    )
   REGISTER_ENUM("FORMAT_A8"       , CAIRO_FORMAT_A8       )
   REGISTER_ENUM("FORMAT_A1"       , CAIRO_FORMAT_A1       )
   REGISTER_ENUM("FORMAT_RGB16_565", CAIRO_FORMAT_RGB16_565)
   REGISTER_ENUM("FORMAT_RGB30"    , CAIRO_FORMAT_RGB30    )

   return 1;
} // >>>

// shapes <<<
int arc(lua_State *L) // <<<
{
   double angle2 = lua_tonumber(L, 6);
   double angle1 = lua_tonumber(L, 5);
   double radius = lua_tonumber(L, 4);
   double yc     = lua_tonumber(L, 3);
   double xc     = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_arc(context, xc, yc, radius, angle1, angle2);
   return 0;
}
// >>>
int arc_negative(lua_State *L) // <<<
{
   double angle2 = lua_tonumber(L, 6);
   double angle1 = lua_tonumber(L, 5);
   double radius = lua_tonumber(L, 4);
   double yc     = lua_tonumber(L, 3);
   double xc     = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_arc_negative(context, xc, yc, radius, angle1, angle2);
   return 0;
} // >>>
int rectangle(lua_State *L) // <<<
{
   double H = lua_tonumber(L, 5);
   double W = lua_tonumber(L, 4);
   double Y = lua_tonumber(L, 3);
   double X = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_rectangle(context, X, Y, W, H);
   return 0;
} // >>>
// >>>

// paths <<<
int move_to(lua_State *L) // <<<
{
   double y = lua_tonumber(L, 3);
   double x = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_move_to(context, x, y);
   return 0;
} // >>>
int line_to(lua_State *L) // <<<
{
   double y = lua_tonumber(L, 3);
   double x = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_line_to(context, x, y);
   return 0;
} // >>>
int curve_to(lua_State *L) // <<<
{
   double y3 = lua_tonumber(L, 7);
   double x3 = lua_tonumber(L, 6);
   double y2 = lua_tonumber(L, 5);
   double x2 = lua_tonumber(L, 4);
   double y1 = lua_tonumber(L, 3);
   double x1 = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_curve_to(context, x1, y1, x2, y2, x3, y3);
   return 0;
} // >>>
int rel_move_to(lua_State *L) // <<<
{
   double dy = lua_tonumber(L, 3);
   double dx = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_rel_move_to(context, dx, dy);
   return 0;
} // >>>
int rel_line_to(lua_State *L) // <<<
{
   double dy = lua_tonumber(L, 3);
   double dx = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_line_to(context, dx, dy);
   return 0;
} // >>>
int rel_curve_to(lua_State *L) // <<<
{
   double dy3 = lua_tonumber(L, 7);
   double dx3 = lua_tonumber(L, 6);
   double dy2 = lua_tonumber(L, 5);
   double dx2 = lua_tonumber(L, 4);
   double dy1 = lua_tonumber(L, 3);
   double dx1 = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_curve_to(context, dx1, dy1, dx2, dy2, dx3, dy3);
   return 0;
} // >>>
int close_path(lua_State *L) // <<<
{
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_close_path(context);
   return 0;
} // >>>
int fill(lua_State *L) // <<<
{
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_fill(context);
   return 0;
} // >>>
int stroke(lua_State *L) // <<<
{
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_stroke(context);
   return 0;
} // >>>
int new_path(lua_State *L) // <<<
{
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_new_path(context);
   return 0;
} // >>>
int new_sub_path(lua_State *L) // <<<
{
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_new_sub_path(context);
   return 0;
} // >>>
// >>>

// surfaces <<<
int image_surface_create(lua_State *L) // <<<
{
   double h = lua_tonumber(L, 3);
   double w = lua_tonumber(L, 2);
   int format = lua_tointeger(L, 1);
   cairo_surface_t *surface = cairo_image_surface_create(format, w, h);
   lua_pushlightuserdata(L, (void*)surface);
   return 1;
} // >>>
int surface_write_to_png(lua_State *L) // <<<
{
   const char *FileName = lua_tostring(L, 2);
   cairo_surface_t *surface = (cairo_surface_t*)lua_topointer(L, 1);
   /* cairo_status_t Status = cairo_surface_write_to_png(surface, FileName); */
   cairo_surface_write_to_png(surface, FileName);
   return 0;
} // >>>
int create(lua_State *L) // <<<
{
   cairo_surface_t *surface = (cairo_surface_t*)lua_topointer(L, 1);
   cairo_t *context = cairo_create(surface);
   lua_pushlightuserdata(L, (void*)context);
   return 1;
} // >>>
int destroy(lua_State *L) // <<<
{
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_destroy(context);
   return 0;
} // >>>
int surface_destroy(lua_State *L) // <<<
{
   cairo_surface_t *surface = (cairo_surface_t*)lua_topointer(L, 1);
   cairo_surface_destroy(surface);
   return 0;
} // >>>
int svg_surface_create(lua_State *L) // <<<
{
   double h = lua_tonumber(L, 3);
   double w = lua_tonumber(L, 2);
   const char *FileName = lua_tostring(L, 1);
   cairo_surface_t *surface = (cairo_surface_t*)cairo_svg_surface_create(FileName, w, h);
   lua_pushlightuserdata(L, (void*)surface);
   return 1;
} // >>>
int pdf_surface_create(lua_State *L) // <<<
{
   double h = lua_tonumber(L, 3);
   double w = lua_tonumber(L, 2);
   const char *FileName = lua_tostring(L, 1);
   cairo_surface_t *surface = (cairo_surface_t*)cairo_pdf_surface_create(FileName, w, h);
   lua_pushlightuserdata(L, (void*)surface);
   return 1;
} // >>>
int ps_surface_create(lua_State *L) // <<<
{
   double h = lua_tonumber(L, 3);
   double w = lua_tonumber(L, 2);
   const char *FileName = lua_tostring(L, 1);
   cairo_surface_t *surface = (cairo_surface_t*)cairo_ps_surface_create(FileName, w, h);
   lua_pushlightuserdata(L, (void*)surface);
   return 1;
} // >>>
// >>>

// transformations <<<
int save(lua_State *L) // <<<
{
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_save(context);
   return 0;
} // >>>
int restore(lua_State *L) // <<<
{
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_restore(context);
   return 0;
} // >>>
int scale(lua_State *L) // <<<
{
   double sy = lua_tonumber(L, 3);
   double sx = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_scale(context, sx, sy);
   return 0;
} // >>>
int rotate(lua_State *L) // <<<
{
   double angle = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_rotate(context, angle);
   return 0;
} // >>>
int translate(lua_State *L) // <<<
{
   double ty = lua_tonumber(L, 3);
   double tx = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_translate(context, tx, ty);
   return 0;
} // >>>
// >>>

// settings <<<
int set_source_rgb(lua_State *L) // <<<
{
   double B = lua_tonumber(L, 4);
   double G = lua_tonumber(L, 3);
   double R = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_set_source_rgb(context, R, G, B);
   return 0;
} // >>>
int set_source_rgba(lua_State *L) // <<<
{
   double A = lua_tonumber(L, 5);
   double B = lua_tonumber(L, 4);
   double G = lua_tonumber(L, 3);
   double R = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_set_source_rgba(context, R, G, B, A);
   return 0;
} // >>>
int set_antialias(lua_State *L) // <<<
{
   int a = lua_tointeger(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_set_antialias(context, a);
   return 0;
} // >>>
int set_dash(lua_State *L) // TODO <<<
{
   /* cairo_set_dash(); */
   return 0;
} // >>>
int set_line_cap(lua_State *L) // <<<
{
   int line_cap = lua_tointeger(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_set_line_cap(context, line_cap);
   return 0;
} // >>>
int set_line_join(lua_State *L) // <<<
{
   int line_join = lua_tointeger(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_set_line_join(context, line_join);
   return 0;
} // >>>
int set_line_width(lua_State *L) // <<<
{
   double width = lua_tonumber(L, 2);
   cairo_t *context = (cairo_t*)lua_topointer(L, 1);
   cairo_set_line_width(context, width);
   return 0;
} // >>>
// >>>

// fonts <<<
// >>>
// >>>

// vim: fmr=<<<,>>> fdm=marker
