/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gap between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "SauceCodePro NFM:size=14:style=Bold" };
static const char dmenufont[]       = "SauceCodePro NFM:size=14:style=Bold";
static const char col_gray1[]       = "#282A36";  /* Bar color */
static const char col_gray2[]       = "#282A36";  /* Border non selected */
static const char col_gray3[]       = "#F8F8F2";  /* Bar text color */
static const char col_gray4[]       = "#F8F8F2";  /* Bar text tag selected */
static const char col_accent[]      = "#7287fd";  /* Tag selected bg, or border selected */
static const char *colors[][3]      = {
	/*               fg         bg          border   */
	[SchemeNorm] = { col_gray3, col_gray1,  col_gray2 },
	[SchemeSel]  = { col_gray4, col_accent, col_accent },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	// { "Gimp",     NULL,       NULL,       0,            1,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ NULL,       NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol   arrange function */
	{ "󰍲",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "󰊓",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accent, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static const char *volumeupcmd[]   = { "sh", "/home/vlad/.local/src/dwm/scripts/volume-helper.sh", "up", NULL };
static const char *volumedowncmd[] = { "sh", "/home/vlad/.local/src/dwm/scripts/volume-helper.sh", "down", NULL };
static const char *volumemutecmd[] = { "sh", "/home/vlad/.local/src/dwm/scripts/volume-helper.sh", "mute", NULL };

static const Key keys[] = {
	/* modifier                     key                    function        argument */
	{ 0,                            XF86XK_AudioMute,        spawn,          {.v = volumemutecmd } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,          {.v = volumeupcmd } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,          {.v = volumedowncmd } },
	{ MODKEY,                       XK_space,                spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                    togglebar,      {0} },
	{ MODKEY,                       XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                    incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                    incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                    setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,               zoom,           {0} },
	{ MODKEY,                       XK_Tab,                  view,           {0} },
	{ MODKEY,                       XK_w,                    killclient,     {0} },
	{ MODKEY,                       XK_t,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,                    setlayout,      {.v = &layouts[2]} },
	// { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                togglefloating, {0} },
	{ MODKEY,                       XK_agrave,               view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave,               tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_m,                    quit,           {0} },
	TAGKEYS(                        XK_ampersand,                          0)
	TAGKEYS(                        XK_eacute,                             1)
	TAGKEYS(                        XK_quotedbl,                           2)
	TAGKEYS(                        XK_apostrophe,                         3)
	TAGKEYS(                        XK_parenleft,                          4)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

