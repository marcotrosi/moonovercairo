#ifndef MOC_H
#define MOC_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <cairo.h>

#define REGISTER_ENUM(n, e) lua_pushliteral(L, n); lua_pushinteger(L, e); lua_settable(L, -3);

int arc(lua_State *L);
int arc_negative(lua_State *L);
int close_path(lua_State *L); 
int create(lua_State *L);
int curve_to(lua_State *L); 
int destroy(lua_State *L);
int fill(lua_State *L);
int image_surface_create(lua_State *L);
int line_to(lua_State *L); 
int luaopen_moc(lua_State *L);
int move_to(lua_State *L); 
int new_path(lua_State *L);
int new_sub_path(lua_State *L);
int rectangle(lua_State *L);
int rel_curve_to(lua_State *L); 
int rel_line_to(lua_State *L); 
int rel_move_to(lua_State *L); 
int restore(lua_State *L);
int restore(lua_State *L); 
int rotate(lua_State *L);
int save(lua_State *L);
int scale(lua_State *L);
int set_antialias(lua_State *L);
int set_line_cap(lua_State *L);
int set_line_join(lua_State *L);
int set_line_width(lua_State *L);
int set_source_rgb(lua_State *L);
int set_source_rgba(lua_State *L);
int stroke(lua_State *L);
int svg_surface_create(lua_State *L);
int pdf_surface_create(lua_State *L);
int ps_surface_create(lua_State *L);
int surface_destroy(lua_State *L);
int surface_write_to_png(lua_State *L);
int translate(lua_State *L);

#endif // MOC_H
