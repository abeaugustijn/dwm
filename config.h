/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;		/* border pixel of windows */
static const unsigned int gappx     = 0;		/* gaps between windows */
static const unsigned int snap      = 32;		/* snap pixel */
static const int showstatus			= 0;		/* show status */
static const int showlabel			= 0;		/* show program label */
static const int showbar            = 1;		/* 0 means no bar */
static const int topbar             = 0;		/* 0 means bottom bar */
static const int vertpad            = 0;		/* vertical padding of bar */
static const int sidepad            = 0;		/* horizontal padding of bar */
static const int horizpadbar        = -10;		/* horizontal padding for statusbar */
static const int vertpadbar         = -10;		/* vertical padding for statusbar */
static const char *fonts[]          = { "SauceCodePro Nerd Font Mono:size=19" };
static const char dmenufont[]       = "SauceCodePro Nerd Font:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
//static const char *tags[] = { "", "", "阮", "", "", "", "", "", "" };
static const char *tags[] = { "", "", "阮" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class		instance	title				tags mask	isfloating	monitor */
	{ NULL,			NULL,		"Firefox Nightly",	1 << 1,		0,			-1 },
	{ "Spotify",	NULL,		NULL,			    1 << 2,		0,			-1 },
	{ NULL,			NULL,		"miniRT",			1 << 0,		1,			-1 },
	{ NULL,			NULL,		"conky",			0,			1,			-1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-b", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selfgcolor, "-sf", normfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *roficmd[] = { "rofi", "-show", "run", NULL };
static const char *browsercmd[] = { "firefox-nightly", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

	/* App launchers */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = roficmd } },

	/* Open terminal */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },

	/* Open browser */
	{ MODKEY,                       XK_c,      spawn,          {.v = browsercmd } },

	/* Select monitor configuration */
	{ MODKEY,                       XK_m,      spawn,          SHCMD("monitor_select.sh") },

	/* Play/pause Spotify */
	{ MODKEY,                       XK_space,  spawn,          SHCMD("play_pause.sh") },

	/* Handle backlight */
	{ 0,          XF86XK_MonBrightnessUp,      spawn,          SHCMD("backlight_increase.sh") },
	{ 0,        XF86XK_MonBrightnessDown,      spawn,          SHCMD("backlight_decrease.sh") },

	/* Handle audio */
	{ 0,         XF86XK_AudioRaiseVolume,      spawn,          SHCMD("audio_increase.sh") },
	{ 0,         XF86XK_AudioLowerVolume,      spawn,          SHCMD("audio_decrease.sh") },
	{ 0,                XF86XK_AudioMute,      spawn,          SHCMD("audio_toggle.sh") },

	/* Toggle bar */
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	/* Client control */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_q,      killclient,     {0} },

	/* Monitor control */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	/* Reload xrdb */
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },

	/* Tags */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)

	/* Quit and reload dwm */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

