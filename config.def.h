/* See LICENSE file for copyright and license details. */

static const unsigned int borderpx  = 3;
static const unsigned int snap      = 32;
static const unsigned int gappih    = 5;
static const unsigned int gappiv    = 5;
static const unsigned int gappoh    = 5;
static const unsigned int gappov    = 5;
static const int smartgaps          = 1;
static const int showbar            = 1;
static const int topbar             = 1;
static const char *fonts[]          = { "Dank Mono:size=13", "Apple Emoji:pixelsize=13" };
static const char dmenufont[]       = "Dank Mono:size=13";
static char normbgcolor[]           = "#2d2d2d";
static char normbordercolor[]       = "#2d2d2d";
static char normfgcolor[]           = "#e6e9ed";
static char selfgcolor[]            = "#2d2d2d";
static char selbordercolor[]        = "#82a0c1";
static char selbgcolor[]            = "#b48cad";
static const char *colors[][3]      = {
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor, selbgcolor,  selbordercolor  },
};

static const char *tags[] = { "system", "general", ">_", "whitespace", "twitch" };

static const Rule rules[] = {
  { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55;
static const int nmaster     = 1;
static const int resizehints = 1;

#include "fibonacci.c"
static const Layout layouts[] = {
  { "[]=",      tile },
  { "><>",      NULL },
  { "[M]",      monocle },
  { "[@]",      spiral },
  { "[\\]",     dwindle },
  { "|M|",      centeredmaster },
  { ">M>",      centeredfloatingmaster },
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
  { MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
  { MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
  { MOD, XK_v,     ACTION##stack, {.i = 0 } },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
  { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },

  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },

  STACKKEYS(MODKEY,                          focus)
  STACKKEYS(MODKEY|ShiftMask,                push)

  { MODKEY,                       XK_e,      spawn,          SHCMD("st -e mutt") },

  { MODKEY,                       XK_Escape, killclient,     {0} },
  { MODKEY|ShiftMask,             XK_Escape, quit,           {0} },

  { MODKEY,                       XK_n,      incnmaster,     {.i = +1 } },
  // { MODKEY|ShiftMask,              XK_n,      spawn,          SHCMD() },

  { MODKEY,                       XK_m,      incnmaster,     {.i = -1 } },
  // { MODKEY|ShiftMask,              XK_m,      spawn,          SHCMD() },

  { MODKEY,                       XK_slash,  defaultgaps,    {0} },

  { MODKEY,                       XK_u,      incrigaps,      {.i = +5 } },
  { MODKEY|ShiftMask,             XK_u,      incrigaps,      {.i = -5 } },

  { MODKEY,                       XK_period, togglefloating, {0} },

  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[5]} },

  { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[3]} },
  { MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[4]} },

  { MODKEY,                       XK_a,      setlayout,      {.v = &layouts[6]} },

  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

  // { MODKEY,                       XK_f,      toggle,         {} },
  // { MODKEY|ShiftMask,             XK_f,      spawn,          {0} },

  { MODKEY,                       XK_g,      spawn,          SHCMD("brave") },
  { MODKEY|ShiftMask,             XK_g,      spawn,          SHCMD("brave --incognito") },

  { MODKEY,                       XK_c,      spawn,          SHCMD("code") },

  // { MODKEY,                       XK_i,      spawn,          SHCMD() },

  { MODKEY,                       XK_r,      spawn,          SHCMD("st -e ranger") },

  // { MODKEY,                       XK_p,      spawn,          SHCMD("idle") },
  // { MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("lock") },

  // { MODKEY,                       XK_o,      spawn,          SHCMD("screen") },

  { MODKEY,                       XK_s,      spawn,          SHCMD("st -e ncmpcpp") },

  // { MODKEY,                       XK_F1,     spawn,          SHCMD() },
  // { MODKEY,                       XK_F3,     spawn,          SHCMD() },
  // { MODKEY,                       XK_F5,     spawn,          SHCMD() },
  // { MODKEY,                       XK_F7,     spawn,          SHCMD() },
  // { MODKEY,                       XK_F9,     spawn,          SHCMD() },
  // { MODKEY,                       XK_F11,    spawn,          SHCMD() },

  { 0, XF86XK_AudioMute,          spawn, SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
  { 0, XF86XK_AudioRaiseVolume,   spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%") },
  { 0, XF86XK_AudioLowerVolume,   spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%") },

  { 0, XF86XK_MonBrightnessUp,    spawn, SHCMD("brightnessctl set +5%") },
  { 0, XF86XK_MonBrightnessDown,  spawn, SHCMD("brightnessctl set 5%-") },

  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_3,                      1)
  TAGKEYS(                        XK_5,                      2)
  TAGKEYS(                        XK_7,                      3)
  TAGKEYS(                        XK_9,                      4)
  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
};

static Button buttons[] = {
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
