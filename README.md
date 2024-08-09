# cssindent, indent css without going crazy

I needed to write some CSS to style an HTML rendering of some man pages.
Sometimes I also write CSS for some simple web applications, most of
which simply generate HTML in the Go/C/Python backend and have
absolutely no JavaScript anyways.

Sometimes I write the CSS without being careful with formatting, or I
copy some badly formatted CSS (e.g. from
[mandoc](https://cvsweb.bsd.lv/~checkout~/mandoc/mandoc.css?rev=1.52)).
I want to format them to my standard: tabs for indentation, no extra
spaces, etc.

I asked for a CSS prettifier that works offline in #web, and that could
be hooked up to vim to prettify on save. And I was called a troll
because "web dev needs web, duh". (There are nice people in #web, and
this small rant is not directed towards #web.)

So here is a simple program to indent CSS. It's not perfect, I'm not
going to read 65535 pages of W3C specifications, but it works for my
purposes.

(I should probably write a yacc parser, but I guess a simple solution
like this works for now.)

## Usage
```sh
cssindent < input.css > output.css
cssindent < inplace.css | sponge inplace.css
```

[`sponge`](https://git.joeyh.name/index.cgi/moreutils.git/plain/sponge.c)
is a rather useful utility that buffers input from standard input and
writes it to a file, which makes in-place file changes easier. (Simply
using the same file for both input and output redirection would cause
the file to be truncated.)
