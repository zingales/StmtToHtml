StmtToHtml
==========

A halide standalone which allows a user to print their stmt to an html file, with linked js and css to allow better readability


To Use
==========
include StmtToHtml.h
change the FOLDER_PATH variable in StmtToHtml.h to reflect where the html file should find the appropriate css and js files
from your halide file call print_to_html(filename, Stmt);
