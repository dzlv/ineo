ineo - Drupal 7 theming toolkit.
================================

A collection of snippets and tools I find myself using recursively for new projects.
It aims to make starting a new theme faster, and provides the tools/overrides to output proper HTML5 markup within Drupal 7.

v 0.1.O Needs cleaning/refactoring.

What it’s not:
- Although some cleaning is done, it is not a "reset" theme in itself.
- This is definitely not a production ready template theme to produce a nice site out of the box in just a few clicks.
- No clicky theme-settings here.
- Most likely it will not reach drupal.org, as it is not meant to be yet another HTML4.9 contrib theme.

Use in conjunction with:
"html5_tools" http://dgo.to/html5_tools
"elements" http://dgo.to/elements
"Modernizr" http://dgo.to/modernizr
"Display Suite" http://dgo.to/ds
"Fences" http://dgo.to/fences
"jQuery Update" http://dgo.to/jquery_update


Usage
-----

The basic strucure is "primo" as base theme, and "ineo" as starter kit.

Start a new subtheme with `make NAME="newthemename"`


ToDo’s / To consider
--------------------

- Remove the custom Modernizr stuff and advocate the use of Modernizr module.
-- https://github.com/Modernizr/Modernizr/issues/713
- The region wrappers pruning is a bit agressive, find a more flexible system.
- More SASS/Compass stuff ?
- Accessible tables, use the scope attributes ?
-- http://dgo.to/1645308
-- http://dgo.to/864006
- collapsible fieldsets have been replaced with HTML5 details elements
-- https://drupal.org/node/1852020


Authors
-------

**Pascal Duez**

+ http://pascalduez.me


License
---------------------

Copyright 2011-2013 Pascal Duez.

Licensed under the GNU General Public License, version 2 - http://www.gnu.org/licenses/gpl-2.0.html
