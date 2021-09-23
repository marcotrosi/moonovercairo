![](./doc/moc_header.png)

# Moon Over Cairo

## Disclaimer

> These are Lua bindings to a subset of the [Cairo](https://www.cairographics.org) vector graphics lib in the making, but I don't know yet in which direction I want to take this.

> **Don't use it yet**. If you are searching Lua bindings to Cairo then check out [these](https://www.cairographics.org/bindings/).

## Motivation

I used Lua bindings to Cairo for one of my projects to draw some images. But they weren't up to date with the latest Lua
version. Also I always wanted to learn the Lua C API, but I avoided it because I thought it's too difficult to learn. 10
years wasted. So I decided to write the bindings myself but only for the functions that I need. I have not yet decided
if I want to have it as close as possible to the C lib, or if I want to make it just a Lua vector graphics lib that uses
the Cairo lib. I also might take the chance to write some simple Cairo examples in C and Lua for the Cairo community.

## ToDo

- bind all functions that I think I might need in the first run
- increase robustness / add error handling
- improve makefile
- improve compilation flags
- create cron job to daily get a diff report of the Cairo repo to update MOC
- decide if the functions shall be just like the C lib or if some parameters shall be optional/have default values
- decide if keeping the bindings simple or using metatables for OOP-like usage
- write some aux functions like a circle drawing function that wraps the arc function (to be decided)
- write documentation ( to be decided )
- write code examples ( to be decided )
