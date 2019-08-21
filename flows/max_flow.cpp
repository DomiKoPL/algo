%!PS-Adobe-3.0
%%Title: stdin
%%For: DomiKo
%%Creator: a2ps version 4.14
%%CreationDate: Sat Aug 17 20:10:16 2019
%%BoundingBox: 24 24 571 818
%%DocumentData: Clean7Bit
%%Orientation: Portrait
%%Pages: 0
%%PageOrder: Ascend
%%DocumentMedia: A4 595 842 0 () ()
%%DocumentNeededResources: font Courier
%%+ font Courier-Bold
%%+ font Helvetica
%%+ font Helvetica-Bold
%%+ font Symbol
%%+ font Times-Bold
%%+ font Times-Roman
%%DocumentProcessColors: Black Blue Green Red 
%%DocumentSuppliedResources: procset a2ps-color-prolog
%%+ encoding ISO-8859-1Encoding
%%EndComments
/a2psdict 200 dict def
a2psdict begin
%%BeginProlog
%%Copyright: (c) 1988, 89, 90, 91, 92, 93 Miguel Santana
%%Copyright: (c) 1995, 96, 97, 98 Akim Demaille, Miguel Santana
% Check PostScript language level.
/languagelevel where {
  pop /gs_languagelevel languagelevel def
} {
  /gs_languagelevel 1 def
} ifelse

% EPSF import as in the Red Book
/BeginInclude {
  /b4_Inc_state save def    		% Save state for cleanup
  /dict_count countdictstack def	% Count objects on dict stack
  /op_count count 1 sub def		% Count objects on operand stack 
  userdict begin
    0 setgray 0 setlinecap
    1 setlinewidth 0 setlinejoin
    10 setmiterlimit [ ] 0 setdash newpath
    gs_languagelevel 1 ne {
      false setstrokeadjust false setoverprint 
    } if
} bind def

/EndInclude {
  count op_count sub { pos } repeat	% Clean up stacks
  countdictstack dict_count sub { end } repeat
  b4_Inc_state restore
} bind def

/BeginEPSF {
  BeginInclude
  /showpage { } def
} bind def

/EndEPSF {
  EndInclude
} bind def

% Page prefeed
/page_prefeed {         % bool -> -
  statusdict /prefeed known {
    statusdict exch /prefeed exch put
  } {
    pop
  } ifelse
} bind def

/deffont {
  findfont exch scalefont def
} bind def

/reencode_font {
  findfont reencode 2 copy definefont pop def
} bind def

% Function c-show (str => -)
% centers text only according to x axis.
/c-show { 
  dup stringwidth pop
  2 div neg 0 rmoveto
  show
} bind def

% Function l-show (str => -)
% prints texts so that it ends at currentpoint
/l-show {
  dup stringwidth pop neg 
  0 
  rmoveto show
} bind def

% center-fit show (str w => -)
% show centered, and scale currentfont so that the width is less than w
/cfshow {
  exch dup stringwidth pop
  % If the title is too big, try to make it smaller
  3 2 roll 2 copy
  gt
  { % if, i.e. too big
    exch div
    currentfont exch scalefont setfont
  } { % ifelse
    pop pop 
  }
  ifelse
  c-show			% center title
} bind def

% Return the y size of the current font
% - => fontsize
/currentfontsize {
  currentfont /FontMatrix get 3 get 1000 mul
} bind def

% reencode the font
% <encoding-vector> <fontdict> -> <newfontdict>
/reencode { %def
  dup length 5 add dict begin
    { %forall
      % <vector> <key> <val>
      1 index /FID ne 
      { def }{ pop pop } ifelse
    } forall
    /Encoding exch def % -

    % Use the font's bounding box to determine the ascent, descent,
    % and overall height; don't forget that these values have to be
    % transformed using the font's matrix.
    % We use `load' because sometimes BBox is executable, sometimes not.
    % Since we need 4 numbers an not an array avoid BBox from being executed
    /FontBBox load aload pop
    FontMatrix transform /Ascent exch def pop
    FontMatrix transform /Descent exch def pop
    /FontHeight Ascent Descent sub def

    % Get the underline position and thickness if they're defined.
    % Use 1 if they are not defined.
    currentdict /FontInfo 2 copy known
    { get
      /UnderlinePosition 2 copy % <FontInfo> /UP <FontInfo> /UP
      2 copy known
      { get }{ pop pop 1 } ifelse
      0 exch FontMatrix transform exch pop
      def % <FontInfo>

      /UnderlineThickness 2 copy % <FontInfo> /UT <FontInfo> /UT
      2 copy known
      { get }{ pop pop 1 } ifelse
      0 exch FontMatrix transform exch pop
      def % <FontInfo>
      pop % -
    }{ pop pop
    } ifelse

    currentdict
  end 
} bind def

% Function print line number (<string> # -)
/# {
  gsave
    sx cw mul neg 2 div 0 rmoveto
    f# setfont
    c-show
  grestore
} bind def

% -------- Some routines to enlight plain b/w printings ---------

% Underline
% width --
/dounderline {
  currentpoint
  gsave
    moveto
    0 currentfont /Descent get currentfontsize mul rmoveto
    0 rlineto
    stroke
  grestore
} bind def

% Underline a string
% string --
/dounderlinestring {
  stringwidth pop
  dounderline
} bind def

/UL {
  /ul exch store
} bind def

% Draw a box of WIDTH wrt current font
% width --
/dobox {
  currentpoint
  gsave
    newpath
    moveto
    0 currentfont /Descent get currentfontsize mul rmoveto
    dup 0 rlineto
    0 currentfont /FontHeight get currentfontsize mul rlineto
    neg 0 rlineto
    closepath
    stroke
  grestore
} bind def

/BX {
  /bx exch store
} bind def

% Box a string
% string --
/doboxstring {
  stringwidth pop
  dobox
} bind def

%
% ------------- Color routines ---------------
%
/FG /setrgbcolor load def

% Draw the background
% width --
/dobackground {
  currentpoint
  gsave
    newpath
    moveto
    0 currentfont /Descent get currentfontsize mul rmoveto
    dup 0 rlineto
    0 currentfont /FontHeight get currentfontsize mul rlineto
    neg 0 rlineto
    closepath
    bgcolor aload pop setrgbcolor
    fill
  grestore
} bind def

% Draw bg for a string
% string --
/dobackgroundstring {
  stringwidth pop
  dobackground
} bind def


/BG {
  dup /bg exch store
  { mark 4 1 roll ] /bgcolor exch store } if
} bind def


/Show {
  bg { dup dobackgroundstring } if
  ul { dup dounderlinestring } if
  bx { dup doboxstring } if
  show
} bind def

% Function T(ab), jumps to the n-th tabulation in the current line
/T {
  cw mul x0 add
  bg { dup currentpoint pop sub dobackground } if
  ul { dup currentpoint pop sub dounderline } if
  bx { dup currentpoint pop sub dobox } if
  y0 moveto
} bind def

% Function n: move to the next line
/n {
  /y0 y0 bfs sub store
  x0 y0 moveto
} bind def

% Function N: show and move to the next line
/N {
  Show
  /y0 y0 bfs sub store
  x0 y0 moveto
} bind def

/S {
  Show
} bind def

%%Copyright: (c) 1988, 89, 90, 91, 92, 93 Miguel Santana
%%Copyright: (c) 1995, 96, 97, 98 Akim Demaille, Miguel Santana
% Function title: prints page header.
% <ct> <rt> <lt> are passed as argument
/title { 
  % 1. Draw the background
  x v get y v get moveto
  0 setgray
  gsave
    0 th 2 div neg rmoveto 
    th setlinewidth
    0.5 0.5 1 setrgbcolor
    pw 0 rlineto stroke
  grestore
  % 2. Border it
  gsave
    0.7 setlinewidth
    pw 0 rlineto
    0 th neg rlineto
    pw neg 0 rlineto
    closepath stroke
  grestore
  % stk: ct rt lt
  x v get y v get th sub 1 add moveto
%%IncludeResource: font Helvetica
  fHelvetica fnfs 0.8 mul scalefont setfont
  % 3. The left title
  gsave
    dup stringwidth pop fnfs 0.8 mul add exch % leave space took on stack
    fnfs 0.8 mul hm rmoveto
    show			% left title
  grestore
  exch
  % stk: ct ltw rt
  % 4. the right title
  gsave
    dup stringwidth pop fnfs 0.8 mul add exch % leave space took on stack
    dup
    pw exch stringwidth pop fnfs 0.8 mul add sub
    hm
    rmoveto
    show			% right title
  grestore
  % stk: ct ltw rtw
  % 5. the center title
  gsave
    pw 3 1 roll
    % stk: ct pw ltw rtw
    3 copy 
    % Move to the center of the left room
    sub add 2 div hm rmoveto
    % What is the available space in here?
    add sub fnfs 0.8 mul sub fnfs 0.8 mul sub
    % stk: ct space_left
%%IncludeResource: font Helvetica-Bold
  fHelvetica-Bold fnfs scalefont setfont
    1 setgray
    cfshow
  grestore
} bind def

% Function border: prints virtual page border
/border { %def
  gsave				% print four sides
    0 setgray
    x v get y v get moveto
    0.7 setlinewidth		% of the square
    pw 0 rlineto
    0 ph neg rlineto
    pw neg 0 rlineto
    closepath stroke
  grestore
} bind def

% Function water: prints a water mark in background
/water { %def
  gsave
    scx scy moveto rotate
%%IncludeResource: font Times-Bold
  fTimes-Bold 100 scalefont setfont
    .97 setgray
    dup stringwidth pop 2 div neg -50 rmoveto
    show
  grestore
} bind def

% Function rhead: prints the right header
/rhead {  %def
  lx ly moveto
  fHelvetica fnfs 0.8 mul scalefont setfont
  l-show
} bind def

% Function footer (cf rf lf -> -)
/footer {
  fHelvetica fnfs 0.8 mul scalefont setfont
  dx dy moveto
  show

  snx sny moveto
  l-show
  
  fnx fny moveto
  c-show
} bind def

% Function print line number (<string> # -)
/# {
  gsave
    sx cw mul neg 2 div 0 rmoveto
    f# setfont
    c-show
  grestore
} bind def
%%BeginResource: procset a2ps-color-prolog 2.0 1

%% Definition of the color faces.
/p {
  0 0 0 FG
  false BG
  false UL
  false BX
  fCourier bfs scalefont setfont
  Show
} bind def

/sy {
  0 0 0 FG
  false BG
  fSymbol bfs scalefont setfont
  Show
} bind def

/k {
  false BG
  false UL
  false BX
  0 0 0.9 FG
  fCourier bfs scalefont setfont
  Show
} bind def

/K {
  false BG
  false UL
  false BX
  0 0 0.8 FG
  fCourier-Bold bfs scalefont setfont
  Show
} bind def

/c {
  false BG
  false UL
  false BX
  0.8 0 0 FG
  fCourier bfs scalefont setfont
  Show
} bind def

/C {
  false BG
  false UL
  false BX
  0.8 0 0 FG
  fCourier-Bold bfs scalefont setfont
  Show
} bind def

/l {
  0 0 0 FG
  0.8 0.8 0 true BG
  false UL
  false BX
  fCourier bfs scalefont setfont
  Show
} bind def

/L {
  0 0 0 FG
  1 1 0 true BG
  false UL
  false BX
  fCourier-Bold bfs scalefont setfont
  Show
} bind def

/str {
  false BG
  false UL
  false BX
  0 0.5 0 FG
  fTimes-Roman bfs scalefont setfont
  Show
} bind def

/e{
  1 0 0 true BG
  false UL
  true BX
  1 1 1 FG
  fHelvetica-Bold bfs scalefont setfont
  Show
} bind def

% Function print line number (<string> # -)
/# {
  gsave
    sx cw mul 2 div neg 0 rmoveto
    f# setfont
    0.8 0.1 0.1 FG
    c-show
  grestore
} bind def
%%EndResource
%%EndProlog
%%BeginSetup
%%IncludeResource: font Courier
%%IncludeResource: font Courier-Bold
%%IncludeResource: font Times-Roman
%%IncludeResource: font Symbol
%%BeginResource: encoding ISO-8859-1Encoding
/ISO-8859-1Encoding [
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/space /exclam /quotedbl /numbersign /dollar /percent /ampersand /quoteright 
/parenleft /parenright /asterisk /plus /comma /minus /period /slash 
/zero /one /two /three /four /five /six /seven 
/eight /nine /colon /semicolon /less /equal /greater /question 
/at /A /B /C /D /E /F /G 
/H /I /J /K /L /M /N /O 
/P /Q /R /S /T /U /V /W 
/X /Y /Z /bracketleft /backslash /bracketright /asciicircum /underscore 
/quoteleft /a /b /c /d /e /f /g 
/h /i /j /k /l /m /n /o 
/p /q /r /s /t /u /v /w 
/x /y /z /braceleft /bar /braceright /asciitilde /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/space /exclamdown /cent /sterling /currency /yen /brokenbar /section 
/dieresis /copyright /ordfeminine /guillemotleft /logicalnot /hyphen /registered /macron 
/degree /plusminus /twosuperior /threesuperior /acute /mu /paragraph /bullet 
/cedilla /onesuperior /ordmasculine /guillemotright /onequarter /onehalf /threequarters /questiondown 
/Agrave /Aacute /Acircumflex /Atilde /Adieresis /Aring /AE /Ccedilla 
/Egrave /Eacute /Ecircumflex /Edieresis /Igrave /Iacute /Icircumflex /Idieresis 
/Eth /Ntilde /Ograve /Oacute /Ocircumflex /Otilde /Odieresis /multiply 
/Oslash /Ugrave /Uacute /Ucircumflex /Udieresis /Yacute /Thorn /germandbls 
/agrave /aacute /acircumflex /atilde /adieresis /aring /ae /ccedilla 
/egrave /eacute /ecircumflex /edieresis /igrave /iacute /icircumflex /idieresis 
/eth /ntilde /ograve /oacute /ocircumflex /otilde /odieresis /divide 
/oslash /ugrave /uacute /ucircumflex /udieresis /yacute /thorn /ydieresis 
] def
%%EndResource
% Initialize page description variables.
/sh 842 def
/sw 595 def
/llx 24 def
/urx 571 def
/ury 818 def
/lly 24 def
/#copies 1 def
/th 20.000000 def
/fnfs 15 def
/bfs 9.442379 def
/cw 5.665427 def

% Dictionary for ISO-8859-1 support
/iso1dict 6 dict begin
  /fCourier ISO-8859-1Encoding /Courier reencode_font
  /fCourier-Bold ISO-8859-1Encoding /Courier-Bold reencode_font
  /fHelvetica ISO-8859-1Encoding /Helvetica reencode_font
  /fHelvetica-Bold ISO-8859-1Encoding /Helvetica-Bold reencode_font
  /fTimes-Bold ISO-8859-1Encoding /Times-Bold reencode_font
  /fTimes-Roman ISO-8859-1Encoding /Times-Roman reencode_font
currentdict end def
/bgcolor [ 0 0 0 ] def
/bg false def
/ul false def
/bx false def
% The font for line numbering
/f# /Helvetica findfont bfs .6 mul scalefont def
/fSymbol /Symbol findfont def
/hm fnfs 0.25 mul def
/pw
   cw 96.400000 mul
def
/ph
   761.999985 th add
def
/pmw 0 def
/pmh 0 def
/v 0 def
/x [
  0
] def
/y [
  pmh ph add 0 mul ph add
] def
/scx sw 2 div def
/scy sh 2 div def
/snx urx def
/sny lly 2 add def
/dx llx def
/dy sny def
/fnx scx def
/fny dy def
/lx snx def
/ly ury fnfs 0.8 mul sub def
/sx 5 def
/tab 8 def
/x0 0 def
/y0 0 def
%%EndSetup


%%Trailer
end
%%EOF
