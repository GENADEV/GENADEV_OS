# Contributing to GENADEV_OS

When contributing to GENADEV_OS, make sure that the changes you wish to make are in line with the project direction. If you are not sure about this, open an issue first, so we can discuss it.

For your first pull request, start with something small to get familiar with the project and its development processes.

## Language

Whilst this project is founded and actively maintained by a German OSDdev group we, as a collective, aim to enable access to the project for anyone, hence the use of english comments and guidelines.

## Coding Style

Here at [GENADEV](https://github.com/GENADEV/) we make use of the syntax formatting tool [Artistic Style](http://astyle.sourceforge.net/).
It is expected that you run this tool before committing; the command can be conveniently invoked using ```make format```.
Commits which have not done this will be rejected.

We use the following rules/arguments: ```--style=allman --indent=force-tab --break-blocks --pad-oper --pad-comma --pad-header --break-one-line-headers --remove-braces --remove-comment-prefix```

**The following informations are from the [official documentation](http://astyle.sourceforge.net/astyle.html).**

- --style=allman
  
  Allman style uses broken braces.
  ```
  int Foo(bool isBar)
  {
      if (isBar)
      {
          bar();
          return 1;
      }
      else
          return 0;
  }
  ```

- --indent=force-tab
  
  Indent using all tab characters, if possible. If a continuation line is not an even number of tabs, spaces will be added at the end. Treat each tab as # spaces (e.g. -T6 / --indent=force-tab=6). # must be between 2 and 20. If no # is set, treats tabs as 4 spaces.

  with indent=force-tab:
  ```
  void Foo() {
  >   if (isBar1
  >   >   >   && isBar2)    // indent of this line can be changed with min-conditional-indent
  >   >   bar();
  }
  ```

- --break-blocks

  Pad empty lines around header blocks (e.g. 'if', 'for', 'while'...).

  ```
  isFoo = true;
  if (isFoo) {
      bar();
  } else {
      anotherBar();
  }
  isBar = false;

  becomes:

  isFoo = true;

  if (isFoo) {
      bar();
  } else {
      anotherBar();
  }

  isBar = false;
  ```
  
- --pad-oper

  Insert space padding around operators. This will also pad commas. Any end of line comments will remain in the original column, if possible. Note that there is no option to unpad. Once padded, they stay padded.

  ```
  if (foo==2)
      a=bar((b-c)*a,d--);

  becomes:

  if (foo == 2)
      a = bar((b - c) * a, d--);
  ```
  
- --pad-comma

  Insert space padding after commas. This is not needed if pad-oper is used. Any end of line comments will remain in the original column, if possible. Note that there is no option to unpad. Once padded, they stay padded.

  ```
  if (isFoo(a,b))
      bar(a,b);

  becomes:

  if (isFoo(a, b))
      bar(a, b);
  ```

- --pad-header

  Insert space padding between a header (e.g. 'if', 'for', 'while'...) and the following paren. Any end of line comments will remain in the original column, if possible. This can be used with unpad-paren to remove unwanted spaces.

  ```
  if(isFoo((a+2), b))
      bar(a, b);

  becomes:

  if (isFoo((a+2), b))
      bar(a, b);
  ```
  
- --break-one-line-headers

  Break one line headers (e.g. 'if', 'while', 'else', ...) from a statement residing on the same line. If the statement is enclosed in braces, the braces will be formatted according to the requested brace style.

  A multi-statement line will NOT be broken if keep-one-line-statements is requested. One line blocks will NOT be broken if keep-one-line-blocks is requested and the header is enclosed in the block.

  ```
  void Foo(bool isFoo)
  {
      if (isFoo1) bar1();

      if (isFoo2) { bar2(); }
  }

  becomes:

  void Foo(bool isFoo)
  {
      if (isFoo1)
          bar1();

      if (isFoo2) {
          bar2();
      }
  }
  ```

- --remove-braces

  Remove braces from conditional statements (e.g. 'if', 'for', 'while'...). The statement must be a single statement on a single line. If --add-braces or --add-one-line-braces is also used the result will be to add braces. Braces will not be removed from "One True Brace Style", --style=1tbs.

  ```
  if (isFoo)
  {
      isFoo = false;
  }

  becomes:

  if (isFoo)
      isFoo = false;
  ```

- --remove-comment-prefix

  Remove the preceding '*' in a multi-line comment that begins a line. A trailing '*', if present, is also removed. Text that is less than one indent is indented to one indent. Text greater than one indent is not changed. Multi-line comments that begin a line, but without the preceding '*', are indented to one indent for consistency. This can slightly modify the indentation of commented out blocks of code. Lines containing all '*' are left unchanged. Extra spacing is removed from the comment close '*/'.

  ```
  /*
   * comment line 1
   * comment line 2
   */

  becomes:

  /*
      comment line 1
      comment line 2
  */
  ```
  
### Comments

Everyone loves long, winding, never ending documentations and comments! 
Okay, maybe not, which is why this section introduces the need for short and consise comments

Try to adapt a scheme like the one you see below:

```
void init_foo() 
{
    int bar; //counter part of 'foo', often used for proof of concept code or examples
} 

//<Meaning of the variable>
#define PGA_ESL_2 0x28382
```
  
Try to avoid this:

```
//This function will initialize foo (REDUNDANT COMMENT) 
void init_foo()
{
        int bar; //Create an integer called bar which does x and y (Partially redundant information such as type name) 
}

// Missing information (what is PGA_ESL_2 and its corresponding value?) 
#define PGA_ESL_2 0x28382
```

## Commits

It is important that you split your work into bite sized commits (the general rule of thumb here is one file = one commit where a header and its corresponding source file are considered one file). When it comes to commit messages, and we cannot stress this enough, please ensure that you use meaningful names.

They have to follow the following structure:

```[new] x``` for new features

```[fix] y``` for stuff that you had to change in order to make something work

```[doc] z``` for changes in the documentation

## Communication

[German OSDev & Lang Dev discord server](https://disboard.org/server/819953014953476126) (For German speakers only)

Or

[Github Discussions](https://github.com/GENADEV/GENADEV_OS/discussions) (For everyone as long as it is on-topic)
