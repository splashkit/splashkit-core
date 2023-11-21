#include <ncursesw/ncurses.h>

int COLORS = 0;
WINDOW * stdscr = nullptr;

extern NCURSES_EXPORT(int) use_default_colors (void){return 0;}

extern NCURSES_EXPORT(int) clear (void){return 0;}				/* generated */
extern NCURSES_EXPORT(int) move (int, int){return 0;}				/* generated */
extern NCURSES_EXPORT(int) refresh (void){return 0;}				/* generated */

extern NCURSES_EXPORT(int) baudrate (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) beep  (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(bool) can_change_color (void){return false;}			/* implemented */
extern NCURSES_EXPORT(int) cbreak (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) clearok (WINDOW *,bool){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) color_content (NCURSES_COLOR_T,NCURSES_COLOR_T*,NCURSES_COLOR_T*,NCURSES_COLOR_T*){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) copywin (const WINDOW*,WINDOW*,int,int,int,int,int,int,int){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) curs_set (int){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) def_prog_mode (void){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) def_shell_mode (void){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) delay_output (int){return 0;}				/* implemented */
extern NCURSES_EXPORT(void) delscreen (SCREEN *){}			/* implemented */
extern NCURSES_EXPORT(int) delwin (WINDOW *){return 0;}				/* implemented */
extern NCURSES_EXPORT(WINDOW *) derwin (WINDOW *,int,int,int,int){return nullptr;}	/* implemented */
extern NCURSES_EXPORT(int) doupdate (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(WINDOW *) dupwin (WINDOW *){return nullptr;}			/* implemented */
extern NCURSES_EXPORT(int) echo (void){return 0;}					/* implemented */
extern NCURSES_EXPORT(int) endwin (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(char) erasechar (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(void) filter (void){}				/* implemented */
extern NCURSES_EXPORT(int) flash (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) flushinp (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(WINDOW *) getwin (FILE *){return nullptr;}			/* implemented */
extern NCURSES_EXPORT(int) halfdelay (int){return 0;}				/* implemented */
extern NCURSES_EXPORT(bool) has_colors (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(bool) has_ic (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(bool) has_il (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(void) idcok (WINDOW *, bool){}			/* implemented */
extern NCURSES_EXPORT(int) idlok (WINDOW *, bool){return 0;}			/* implemented */
extern NCURSES_EXPORT(void) immedok (WINDOW *, bool){}			/* implemented */
extern NCURSES_EXPORT(WINDOW *) initscr (void){return nullptr;}				/* implemented */
extern NCURSES_EXPORT(int) init_color (NCURSES_COLOR_T,NCURSES_COLOR_T,NCURSES_COLOR_T,NCURSES_COLOR_T){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) init_pair (NCURSES_PAIRS_T,NCURSES_COLOR_T,NCURSES_COLOR_T){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) intrflush (WINDOW *,bool){return 0;}			/* implemented */
extern NCURSES_EXPORT(bool) isendwin (void){return false;}				/* implemented */
extern NCURSES_EXPORT(bool) is_linetouched (WINDOW *,int){return false;}		/* implemented */
extern NCURSES_EXPORT(bool) is_wintouched (WINDOW *){return false;}			/* implemented */
extern NCURSES_EXPORT(NCURSES_CONST char *) keyname (int){return nullptr;}		/* implemented */
extern NCURSES_EXPORT(int) keypad (WINDOW *,bool){return 0;}			/* implemented */
extern NCURSES_EXPORT(char) killchar (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) leaveok (WINDOW *,bool){return 0;}			/* implemented */
extern NCURSES_EXPORT(char *) longname (void){return nullptr;}				/* implemented */
extern NCURSES_EXPORT(int) meta (WINDOW *,bool){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) mvcur (int,int,int,int){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) mvderwin (WINDOW *, int, int){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) mvprintw (int,int, const char *,...)		/* implemented */
		GCC_PRINTFLIKE(3,4){return 0;}
extern NCURSES_EXPORT(int) mvscanw (int,int, NCURSES_CONST char *,...)	/* implemented */
		GCC_SCANFLIKE(3,4){return 0;}
extern NCURSES_EXPORT(int) mvwin (WINDOW *,int,int){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) mvwprintw (WINDOW*,int,int, const char *,...)	/* implemented */
		GCC_PRINTFLIKE(4,5){return 0;}
extern NCURSES_EXPORT(int) mvwscanw (WINDOW *,int,int, NCURSES_CONST char *,...)	/* implemented */
		GCC_SCANFLIKE(4,5){return 0;}
extern NCURSES_EXPORT(int) napms (int){return 0;}					/* implemented */
extern NCURSES_EXPORT(WINDOW *) newpad (int,int){return nullptr;}		       	/* implemented */
extern NCURSES_EXPORT(SCREEN *) newterm (NCURSES_CONST char *,FILE *,FILE *){return nullptr;}	/* implemented */
extern NCURSES_EXPORT(WINDOW *) newwin (int,int,int,int){return nullptr;}	       	/* implemented */
extern NCURSES_EXPORT(int) nl (void){return 0;}					/* implemented */
extern NCURSES_EXPORT(int) nocbreak (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) nodelay (WINDOW *,bool){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) noecho (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) nonl (void){return 0;}					/* implemented */
extern NCURSES_EXPORT(void) noqiflush (void){}				/* implemented */
extern NCURSES_EXPORT(int) noraw (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) notimeout (WINDOW *,bool){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) overlay (const WINDOW*,WINDOW *){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) overwrite (const WINDOW*,WINDOW *){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) pair_content (NCURSES_PAIRS_T,NCURSES_COLOR_T*,NCURSES_COLOR_T*){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) pechochar (WINDOW *, const chtype){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) pnoutrefresh (WINDOW*,int,int,int,int,int,int){return 0;}/* implemented */
extern NCURSES_EXPORT(int) prefresh (WINDOW *,int,int,int,int,int,int){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) printw (const char *,...)			/* implemented */
		GCC_PRINTFLIKE(1,2){return 0;}
extern NCURSES_EXPORT(int) putwin (WINDOW *, FILE *){return 0;}			/* implemented */
extern NCURSES_EXPORT(void) qiflush (void){}				/* implemented */
extern NCURSES_EXPORT(int) raw (void){return 0;}					/* implemented */
extern NCURSES_EXPORT(int) resetty (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) reset_prog_mode (void){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) reset_shell_mode (void){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) ripoffline (int, int (*)(WINDOW *, int)){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) savetty (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) scanw (NCURSES_CONST char *,...)		/* implemented */
		GCC_SCANFLIKE(1,2){return 0;}
extern NCURSES_EXPORT(int) scr_dump (const char *){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) scr_init (const char *){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) scrollok (WINDOW *,bool){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) scr_restore (const char *){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) scr_set (const char *){return 0;}			/* implemented */
extern NCURSES_EXPORT(SCREEN *) set_term (SCREEN *){return nullptr;}			/* implemented */
extern NCURSES_EXPORT(int) slk_attroff (const chtype){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) slk_attron (const chtype){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) slk_attrset (const chtype){return 0;}			/* implemented */
extern NCURSES_EXPORT(attr_t) slk_attr (void){return (attr_t){};}				/* implemented */
extern NCURSES_EXPORT(int) slk_attr_set (const attr_t,NCURSES_PAIRS_T,void*){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) slk_clear (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) slk_color (NCURSES_PAIRS_T){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) slk_init (int){return 0;}				/* implemented */
extern NCURSES_EXPORT(char *) slk_label (int){return nullptr;}				/* implemented */
extern NCURSES_EXPORT(int) slk_noutrefresh (void){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) slk_refresh (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) slk_restore (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) slk_set (int,const char *,int){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) slk_touch (void){return 0;}	      	       		/* implemented */
extern NCURSES_EXPORT(int) start_color (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(WINDOW *) subpad (WINDOW *, int, int, int, int){return nullptr;}	/* implemented */
extern NCURSES_EXPORT(WINDOW *) subwin (WINDOW *, int, int, int, int){return nullptr;}	/* implemented */
extern NCURSES_EXPORT(int) syncok (WINDOW *, bool){return 0;}			/* implemented */
extern NCURSES_EXPORT(chtype) termattrs (void){return 0;}				/* implemented */
extern NCURSES_EXPORT(char *) termname (void){return nullptr;}				/* implemented */
extern NCURSES_EXPORT(int) typeahead (int){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) ungetch (int){return 0;}				/* implemented */
extern NCURSES_EXPORT(void) use_env (bool){}				/* implemented */
extern NCURSES_EXPORT(void) use_tioctl (bool){}				/* implemented */
extern NCURSES_EXPORT(int) vidattr (chtype){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) vidputs (chtype, NCURSES_OUTC){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) vwprintw (WINDOW *, const char *,va_list){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) vwscanw (WINDOW *, NCURSES_CONST char *,va_list){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) waddch (WINDOW *, const chtype){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) waddchnstr (WINDOW *,const chtype *,int){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) waddnstr (WINDOW *,const char *,int){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) wattr_on (WINDOW *, attr_t, void *){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) wattr_off (WINDOW *, attr_t, void *){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) wbkgd (WINDOW *, chtype){return 0;}			/* implemented */
extern NCURSES_EXPORT(void) wbkgdset (WINDOW *,chtype){}			/* implemented */
extern NCURSES_EXPORT(int) wborder (WINDOW *,chtype,chtype,chtype,chtype,chtype,chtype,chtype,chtype){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) wchgat (WINDOW *, int, attr_t, NCURSES_PAIRS_T, const void *){return 0;}/* implemented */
extern NCURSES_EXPORT(int) wclear (WINDOW *){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) wclrtobot (WINDOW *){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) wclrtoeol (WINDOW *){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) wcolor_set (WINDOW*,NCURSES_PAIRS_T,void*){return 0;}		/* implemented */
extern NCURSES_EXPORT(void) wcursyncup (WINDOW *){}			/* implemented */
extern NCURSES_EXPORT(int) wdelch (WINDOW *){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) wechochar (WINDOW *, const chtype){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) werase (WINDOW *){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) wgetch (WINDOW *){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) wgetnstr (WINDOW *,char *,int){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) whline (WINDOW *, chtype, int){return 0;}		/* implemented */
extern NCURSES_EXPORT(chtype) winch (WINDOW *){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) winchnstr (WINDOW *, chtype *, int){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) winnstr (WINDOW *, char *, int){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) winsch (WINDOW *, chtype){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) winsdelln (WINDOW *,int){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) winsnstr (WINDOW *, const char *,int){return 0;}	/* implemented */
extern NCURSES_EXPORT(int) wmove (WINDOW *,int,int){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) wnoutrefresh (WINDOW *){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) wprintw (WINDOW *, const char *,...)		/* implemented */
		GCC_PRINTFLIKE(2,3){return 0;}
extern NCURSES_EXPORT(int) wredrawln (WINDOW *,int,int){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) wrefresh (WINDOW *){return 0;}				/* implemented */
extern NCURSES_EXPORT(int) wscanw (WINDOW *, NCURSES_CONST char *,...)	/* implemented */
		GCC_SCANFLIKE(2,3){return 0;}
extern NCURSES_EXPORT(int) wscrl (WINDOW *,int){return 0;}			/* implemented */
extern NCURSES_EXPORT(int) wsetscrreg (WINDOW *,int,int){return 0;}		/* implemented */
extern NCURSES_EXPORT(void) wsyncdown (WINDOW *){}			/* implemented */
extern NCURSES_EXPORT(void) wsyncup (WINDOW *){}				/* implemented */
extern NCURSES_EXPORT(void) wtimeout (WINDOW *,int){}			/* implemented */
extern NCURSES_EXPORT(int) wtouchln (WINDOW *,int,int,int){return 0;}		/* implemented */
extern NCURSES_EXPORT(int) wvline (WINDOW *,chtype,int){return 0;}		/* implemented */