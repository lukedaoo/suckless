/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { 
    "Comic Mono:style=Normal:size=12", 
    "monospace:size=12",
    "Font Awesome 6 Free Regular:style=Regular:size=12" 
};
static const char dmenufont[]       = "Comic Mono:style=Normal:size=12";
/* default color */
/*
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
*/
/* -------------- */
/* ayu dark */ 
static const char col_gray1[]       = "#0A0E14";
static const char col_gray2[]       = "#1D202F";
static const char col_gray3[]       = "#F9F9F9";
static const char col_gray4[]       = "#CBCCC6";
static const char col_cyan[]        = "#2d2c2b";
/* -------------- */
/* carbon */ 
/*
static const char col_gray1[]       = "#191716";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#2d2c2b";
*/
/* -------------- */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};
static const char default_terminal[] = "kitty";

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const char browser1[] = "Google-chrome"; /* "Microsoft-edge", "Firefox" */
static const char browser2[] = "Microsoft-edge"; 
static const char browser3[] = "firefox"; 
static const char browser4[] = "LibreWolf"; 

static const char ferdium[] = "Ferdium";
static const char mail[] = "thunderbird";
static const char idea[] = "jetbrains-idea-ce";

static const char slack[] = "Slack";
static const char discord[] = "discord";
static const char teams[] = "teams-for-linux";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ browser1,  NULL,       NULL,       1 << 1,       0,           -1 },
	{ browser2,  NULL,       NULL,       1 << 1,       0,           -1 },
	{ browser3,  NULL,       NULL,       1 << 1,       0,           -1 },
	{ browser4,  NULL,       NULL,       1 << 1,       0,           -1 },

	{ ferdium,  NULL,       NULL,       1 << 7,       0,           -1 },
	{ mail,  NULL,       NULL,       1 << 6,       0,           -1 },
	{ idea,  NULL,       NULL,       1 << 5,       0,           -1 },

	{ default_terminal,  NULL,       NULL,       1 << 0,       0,           -1 },
	{ slack,  NULL,       NULL,       1 << 2,       0,           -1 },
	{ discord,  NULL,       NULL,       1 << 3,       0,           -1 },
	{ teams,  NULL,       NULL,       1 << 3,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define ALT Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ ALT,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ ALT|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ALT|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ ALT|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }
#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { default_terminal, NULL };
/* If you use amixer, use this instead. Thanks go to DaniOrt3ga. */
static const char *upvol[] = { "/usr/bin/amixer", "set", "Master", "5%+", NULL };
static const char *downvol[] = { "/usr/bin/amixer", "set", "Master", "5%-", NULL };
static const char *mutevol[] = { "/usr/bin/amixer", "set", "Master", "toggle", NULL };
static const char *mute_mic[] = {"/usr/bin/amixer", "set", "Capture", "toggle", NULL };

/* To use light add this to the constant definition section. Thanks Hritik14. */
static const char *light_up[] = {"/usr/bin/light", "-A", "10", NULL};
static const char *light_down[] = {"/usr/bin/light", "-U", "10", NULL};

static const char *take_note[] = {"take_note", NULL};
static const char *screenshot[] = {"/usr/bin/flameshot", "gui", NULL };

static const char *next_music[] = {"playerctl", "next", NULL};
static const char *previous_music[] = {"playerctl", "previous", NULL};
static const char *play_pause_music[] = {"playerctl", "play-pause", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },
	{ ALT,                          XK_r,      incnmaster,     {.i = +1 } },
	{ ALT|ShiftMask,                XK_r,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} }, 
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	
	/* layouts */
	{ ALT,                          XK_t,      setlayout,      {.v = &layouts[0]} },
	{ ALT,                          XK_space,  setlayout,      {.v = &layouts[1]} },
	{ ALT,                          XK_f,      setlayout,      {.v = &layouts[2]} },
	{ ALT,                          XK_u,      setlayout,      {.v = &layouts[3]} },
	{ ALT,                          XK_o,      setlayout,      {.v = &layouts[4]} },
	{ ALT|ShiftMask,                XK_f,      setlayout,      {0} },
	{ ALT|ShiftMask,                XK_space,  togglefloating, {0} }, 
	{ ALT,                          XK_F11,      fullscreen,     {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/* end layouts */
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ 0,                       	    XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       	    XF86XK_AudioMute, spawn, {.v = mutevol } },
	{ 0,                       	    XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	{ 0,                       	    XF86XK_AudioNext, spawn, {.v = next_music   } },
	{ 0,                       	    XF86XK_AudioPrev, spawn, {.v = previous_music   } },
	{ 0,                       	    XF86XK_AudioPlay, spawn, {.v = play_pause_music   } },
	{ 0,				            XF86XK_MonBrightnessUp,		spawn,	{.v = light_up} },
	{ 0,				            XF86XK_MonBrightnessDown,	spawn,	{.v = light_down} },
	{ 0,				            XF86XK_AudioMicMute,	spawn,	{.v = mute_mic} },
	{ ALT,                          XK_s,      show,           {0} },
	{ ALT|ShiftMask,                XK_s,      showall,        {0} },
	{ ALT,                          XK_h,      hide,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_minus,      quit,           {0} },
	{ MODKEY,                       XK_n,      spawn,           {.v = take_note} },
	{ MODKEY,                       XK_F4,      spawn,           {.v = screenshot} },
	{ MODKEY,                       XK_Print,      spawn,           {.v = screenshot} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
