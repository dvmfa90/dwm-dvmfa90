/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 0;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "$HOME/bar.sh"; /* Alternate bar launch command */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_yellow[]      = "#F5F508";
static const char col_white[]      = "#FFFFFF";
static const char col_red[]      = "#FD0707";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_white }, 
	[SchemeSel]  = { col_gray4, col_cyan,  col_yellow  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
#define MOD4 Mod4Mask  /*Windows key*/
#define ALT Mod1Mask /*Alt key*/
#define TAGKEYS(KEY,TAG) \
	{ ALT,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MOD4|ControlMask,            KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ALT|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MOD4|ControlMask|ShiftMask,  KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

//#include "push.c"
#include "movestack.c"
static Key keys[] = {
	/* modifier                                 key                    function        argument */
	{ MOD4,                                     XK_p,                   spawn,          {.v = dmenucmd } }, // Opens dmenu
	{ MOD4|ShiftMask,                           XK_Return,              spawn,          {.v = termcmd } }, // Opens terminal defined above
	{ MOD4,                                     XK_b,                   togglebar,      {0} }, //
	{ MOD4,                                     XK_Right,               focusstack,     {.i = +1 } },
	{ MOD4,                                     XK_Left,                focusstack,     {.i = -1 } },
	{ MOD4|ControlMask,                         XK_Right,               incnmaster,     {.i = +1 } }, // Within floating view you can change how windows displays
	{ MOD4|ControlMask,                         XK_Left,                incnmaster,     {.i = -1 } }, // Within floating view you can change how windows displays
	{ MOD4|ALT,                                 XK_Left,                setmfact,       {.f = -0.05} }, // Within floating view increases the window size on the collumn you are
	{ MOD4|ALT,                                 XK_Right,               setmfact,       {.f = +0.05} }, // Within floating view decreases the window size on the collumn you are
	{ MOD4|ShiftMask,                           XK_Right,               movestack,      {.i = +1 } },
	{ MOD4|ShiftMask,                           XK_Left,                movestack,      {.i = -1 } },
	{ MOD4|ShiftMask,                           XK_Return,              zoom,           {0} }, // Within floating view moves selected window to the main one
	{ MOD4,                                     XK_Tab,                 view,           {0} }, // moves to previus/next workspace you were
	{ MOD4,             		                XK_c,                   killclient,     {0} }, // kills the selected window
	{ MOD4,                                     XK_y,                   setlayout,      {.v = &layouts[0]} }, // changes to float window mode
	{ MOD4,                                     XK_m,                   setlayout,      {.v = &layouts[2]} },  /*FULLSCREEN*/
	{ MOD4,		                                XK_comma,               cyclelayout,    {.i = -1 } },
	{ MOD4,                                     XK_period,              cyclelayout,    {.i = +1 } },
	{ MOD4,                                     XK_space,               setlayout,      {0} },
	{ MOD4|ShiftMask,                           XK_space,               togglefloating, {0} },
	{ MOD4,                                     XK_End,                 moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MOD4,                                     XK_Home,                moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MOD4,                                     XK_Next,                moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MOD4,                                     XK_Delete,              moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MOD4|ShiftMask,                           XK_End,                 moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MOD4|ShiftMask,                           XK_Home,                moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MOD4|ShiftMask,                           XK_Next,                moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MOD4|ShiftMask,                           XK_Delete,              moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MOD4|ControlMask,                         XK_Home,                moveresizeedge, {.v = "t"} },
	{ MOD4|ControlMask,                         XK_End,                 moveresizeedge, {.v = "b"} },
	{ MOD4|ControlMask,                         XK_Delete,              moveresizeedge, {.v = "l"} },
	{ MOD4|ControlMask,                         XK_Next,                moveresizeedge, {.v = "r"} },
	{ MOD4|ControlMask|ShiftMask,               XK_Home,                moveresizeedge, {.v = "T"} },
	{ MOD4|ControlMask|ShiftMask,               XK_End,                 moveresizeedge, {.v = "B"} },
	{ MOD4|ControlMask|ShiftMask,               XK_Delete,              moveresizeedge, {.v = "L"} },
	{ MOD4|ControlMask|ShiftMask,               XK_Next,                moveresizeedge, {.v = "R"} },
	{ MOD4,                                     XK_0,                   view,           {.ui = ~0 } },
	{ MOD4|ShiftMask,                           XK_0,                   tag,            {.ui = ~0 } },
	{ ALT,                                      XK_Left,                focusmon,       {.i = +1 } }, //changes foccus to next screen
	{ ALT,                                      XK_Right,               focusmon,       {.i = -1 } }, //changes foccus to next screen
	{ ALT|ShiftMask,                            XK_Left,                tagmon,         {.i = +1 } }, // moves select window to next monitor
	{ ALT|ShiftMask,                            XK_Right,               tagmon,         {.i = -1 } }, // moves select window to next monitor
	{ MOD4|ShiftMask,                           XK_Down,                pushdown,       {0} }, // Move window down
	{ MOD4|ShiftMask,                           XK_Up,                  pushup,         {0} }, //move window up
	{ MOD4|ShiftMask,                           XK_j,                   pushdown,       {0} }, // Move window down
	{ MOD4|ShiftMask,                           XK_k,                   pushup,         {0} }, //move window up
	{ ALT,                                      XK_h,                   focusmon,       {.i = +1 } }, //changes foccus to next screen
	{ ALT,                                      XK_l,                   focusmon,       {.i = -1 } }, //changes foccus to next screen
	{ ALT|ShiftMask,                            XK_h,                   tagmon,         {.i = +1 } }, // moves select window to next monitor
	{ ALT|ShiftMask,                            XK_l,                   tagmon,         {.i = -1 } }, // moves select window to next monitor
	{ MOD4,                                     XK_l,                   focusstack,     {.i = +1 } },
	{ MOD4,                                     XK_h,                   focusstack,     {.i = -1 } },
	{ MOD4|ControlMask,                         XK_l,                   incnmaster,     {.i = +1 } }, // Within floating view you can change how windows displays
	{ MOD4|ControlMask,                         XK_h,                   incnmaster,     {.i = -1 } }, // Within floating view you can change how windows displays
	{ MOD4|ALT,                                 XK_h,                   setmfact,       {.f = -0.05} }, // Within floating view increases the window size on the collumn you are
	{ MOD4|ALT,                                 XK_l,                   setmfact,       {.f = +0.05} }, // Within floating view decreases the window size on the collumn you are
	{ MOD4|ShiftMask,                           XK_l,                   movestack,      {.i = +1 } },
	{ MOD4|ShiftMask,                           XK_h,                   movestack,      {.i = -1 } },
	TAGKEYS(                                    XK_1,                      0)
	TAGKEYS(                                    XK_2,                      1)
	TAGKEYS(                                    XK_3,                      2)
	TAGKEYS(                                    XK_4,                      3)
	TAGKEYS(                                    XK_5,                      4)
	TAGKEYS(                                    XK_6,                      5)
	TAGKEYS(                                    XK_7,                      6)
	TAGKEYS(                                    XK_8,                      7)
	TAGKEYS(                                    XK_9,                      8)
	// ALTERNATIVE with NUMPAD
	TAGKEYS(                                    XK_KP_End,                      0)
	TAGKEYS(                                    XK_KP_Down,                     1)
	TAGKEYS(                                    XK_KP_Page_Down,                2)
	TAGKEYS(                                    XK_KP_Left,                     3)
	TAGKEYS(                                    XK_KP_Begin,                    4)
	TAGKEYS(                                    XK_KP_Right,                    5)
	TAGKEYS(                                    XK_KP_Home,                     6)
	TAGKEYS(                                    XK_KP_Up,                       7)
	TAGKEYS(                                    XK_KP_Page_Up,                  8)
	{ MOD4|ShiftMask,                           XK_q,      quit,           {0} }, //quit dwm
	{ MOD4|ShiftMask,                           XK_r,      quit,           {1} }, //restart dwm
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MOD4,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MOD4,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MOD4,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MOD4,         Button1,        tag,            {0} },
	{ ClkTagBar,            MOD4,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

