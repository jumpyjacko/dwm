/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 4; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int rmaster =
    0; /* 1 means master-area is initially on the right */
static const unsigned int gappih = 5; /* horiz inner gap between windows */
static const unsigned int gappiv = 5; /* vert inner gap between windows */
static const unsigned int gappoh =
    5; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov =
    5; /* vert outer gap between windows and screen edge */
static const int smartgaps =
    0; /* 1 means no outer gap when there is only one window */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
static const int focusonwheel = 0;
static const char *fonts[] = {"mononoki Nerd Font:size=12"};
static const char dmenufont[] = "mononoki Nerd Font:size=24";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_lightgray[] = "#919191";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_lightgray, col_lightgray},
};

/* tagging */
static const char *tags[] = {"一", "二", "三", "四", "五"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor
       float x,y,w,h         floatborderpx*/
    // {"Gimp", NULL, NULL, 0, 1, -1, 50, 50, 500, 500, 4},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1, 50, 50, 500, 500, 4},
    {"TermMemo", NULL, NULL, 0, 1, -1, 50, 50, 1412, 664, 4},
};

/* layout(s) */
static const float mfact = 0.525; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;     /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},        {"|||", col},
    {"|M|", centeredmaster}, {">M>", centeredfloatingmaster},
    {"HHH", grid},           {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = {"dmenu_run ", "-m",  dmenumon,      "-fn",
//                                  dmenufont,    "-nb", col_gray1,     "-nf",
//                                  col_gray3,    "-sb", col_lightgray, "-sf",
//                                  col_gray4,    NULL};
static const char *dmenucmd[] = {"j4-dmenu-desktop", "--dmenu='dmenu_run -m",
                                 dmenumon,           "-fn",
                                 dmenufont,          "-nb",
                                 col_gray1,          "-nf",
                                 col_gray3,          "-sb",
                                 col_lightgray,      "-sf",
                                 col_gray4,          "' ",
                                 "--term='kitty'",   NULL};
static const char *termcmd[] = {"kitty", NULL};
// static const char *lightdown[]   = { "light", "-U", "1" };
// static const char *lightup[]     = { "light", "-A", "1" };
static const char *slockcmd[] = {"slock", NULL};

#include "movestack.c"
static Key keys[] = {
    /* modifier                     key        function        argument */
    // {MODKEY, XK_space, spawn, {.v = dmenucmd}},
    {MODKEY, XK_space, spawn,
     SHCMD("j4-dmenu-desktop --dmenu='dmenu -i -m 0 -fn \"mononoki Nerd Font:size=24\" -nb \"#222222\" -nf \"#bbbbbb\" -sb \"#919191\" -sf \"#eeeeee\"' --term='kitty'")},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_F2, spawn, SHCMD("cd ~/shell_scripts && ./change_brightness dec")},
    {MODKEY, XK_F3, spawn, SHCMD("cd ~/shell_scripts && ./change_brightness inc")},
    {MODKEY, XK_F6, spawn, SHCMD("cd ~/shell_scripts && ./change_volume mute")},
    {MODKEY, XK_F7, spawn, SHCMD("cd ~/shell_scripts && ./change_volume down")},
    {MODKEY, XK_F8, spawn, SHCMD("cd ~/shell_scripts && ./change_volume up")},
    {MODKEY | ControlMask, XK_h, spawn, SHCMD("kitty --class TermMemo -T hotkeys -o font_size=12 'cd ~/shell_scripts/ && ./dwm_hotkeys'")},
    {MODKEY | ShiftMask, XK_s, spawn,
     SHCMD(
         "maim -b 2 -usD /home/jackson/Images/$(date +%d_%m_%Y_%H-%M-%S).png")},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_n, focusstack, {.i = +1}},
    {MODKEY, XK_e, focusstack, {.i = -1}},
    //	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    //	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    {MODKEY, XK_h, setmfact, {.f = -0.01}},
    {MODKEY, XK_i, setmfact, {.f = +0.01}},
    {MODKEY | ShiftMask, XK_n, movestack, {.i = +1}},
    {MODKEY | ShiftMask, XK_e, movestack, {.i = -1}},
    //	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
    //	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
    //	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
    //	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
    //	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
    //	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
    {MODKEY | Mod4Mask, XK_0, togglegaps, {0}},
    {MODKEY | Mod4Mask | ShiftMask, XK_0, defaultgaps, {0}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_w, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_c, setlayout, {.v = &layouts[3]}},
    {MODKEY, XK_u, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_o, setlayout, {.v = &layouts[5]}},
    {MODKEY, XK_g, setlayout, {.v = &layouts[6]}},
    {MODKEY | ControlMask, XK_comma, cyclelayout, {.i = -1}},
    {MODKEY | ControlMask, XK_period, cyclelayout, {.i = +1}},
    {MODKEY, XK_p, setlayout, {0}},
    {MODKEY | ShiftMask, XK_p, togglefloating, {0}},
    {MODKEY, XK_r, togglermaster, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_l, spawn, {.v = slockcmd}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
