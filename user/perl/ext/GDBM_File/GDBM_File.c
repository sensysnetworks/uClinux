/*
 * This file was generated automatically by xsubpp version 1.9508 from the 
 * contents of GDBM_File.xs. Do not edit this file, edit GDBM_File.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "GDBM_File.xs"
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include <gdbm.h>
#include <fcntl.h>

typedef struct {
	GDBM_FILE 	dbp ;
	SV *    filter_fetch_key ;
	SV *    filter_store_key ;
	SV *    filter_fetch_value ;
	SV *    filter_store_value ;
	int     filtering ;
	} GDBM_File_type;

typedef GDBM_File_type * GDBM_File ;
typedef datum datum_key ;
typedef datum datum_value ;

#define ckFilter(arg,type,name)					\
	if (db->type) {						\
	    SV * save_defsv ;					\
            /* printf("filtering %s\n", name) ;*/		\
	    if (db->filtering)					\
	        croak("recursion detected in %s", name) ;	\
	    db->filtering = TRUE ;				\
	    save_defsv = newSVsv(DEFSV) ;			\
	    sv_setsv(DEFSV, arg) ;				\
	    PUSHMARK(sp) ;					\
	    (void) perl_call_sv(db->type, G_DISCARD|G_NOARGS); 	\
	    sv_setsv(arg, DEFSV) ;				\
	    sv_setsv(DEFSV, save_defsv) ;			\
	    SvREFCNT_dec(save_defsv) ;				\
	    db->filtering = FALSE ;				\
	    /*printf("end of filtering %s\n", name) ;*/		\
	}



#define GDBM_BLOCKSIZE 0 /* gdbm defaults to stat blocksize */

typedef void (*FATALFUNC)();

#ifndef GDBM_FAST
static int
not_here(char *s)
{
    croak("GDBM_File::%s not implemented on this architecture", s);
    return -1;
}
#endif

/* GDBM allocates the datum with system malloc() and expects the user
 * to free() it.  So we either have to free() it immediately, or have
 * perl free() it when it deallocates the SV, depending on whether
 * perl uses malloc()/free() or not. */
static void
output_datum(pTHX_ SV *arg, char *str, int size)
{
#if !defined(MYMALLOC) || (defined(MYMALLOC) && defined(PERL_POLLUTE_MALLOC) && !defined(LEAKTEST))
	sv_usepvn(arg, str, size);
#else
	sv_setpvn(arg, str, size);
	safesysfree(str);
#endif
}

/* Versions of gdbm prior to 1.7x might not have the gdbm_sync,
   gdbm_exists, and gdbm_setopt functions.  Apparently Slackware
   (Linux) 2.1 contains gdbm-1.5 (which dates back to 1991).
*/
#ifndef GDBM_FAST
#define gdbm_exists(db,key) not_here("gdbm_exists")
#define gdbm_sync(db) (void) not_here("gdbm_sync")
#define gdbm_setopt(db,optflag,optval,optlen) not_here("gdbm_setopt")
#endif

static double
constant(char *name, int arg)
{
    errno = 0;
    switch (*name) {
    case 'A':
	break;
    case 'B':
	break;
    case 'C':
	break;
    case 'D':
	break;
    case 'E':
	break;
    case 'F':
	break;
    case 'G':
	if (strEQ(name, "GDBM_CACHESIZE"))
#ifdef GDBM_CACHESIZE
	    return GDBM_CACHESIZE;
#else
	    goto not_there;
#endif
	if (strEQ(name, "GDBM_FAST"))
#ifdef GDBM_FAST
	    return GDBM_FAST;
#else
	    goto not_there;
#endif
	if (strEQ(name, "GDBM_FASTMODE"))
#ifdef GDBM_FASTMODE
	    return GDBM_FASTMODE;
#else
	    goto not_there;
#endif
	if (strEQ(name, "GDBM_INSERT"))
#ifdef GDBM_INSERT
	    return GDBM_INSERT;
#else
	    goto not_there;
#endif
	if (strEQ(name, "GDBM_NEWDB"))
#ifdef GDBM_NEWDB
	    return GDBM_NEWDB;
#else
	    goto not_there;
#endif
	if (strEQ(name, "GDBM_NOLOCK"))
#ifdef GDBM_NOLOCK
	    return GDBM_NOLOCK;
#else
	    goto not_there;
#endif
	if (strEQ(name, "GDBM_READER"))
#ifdef GDBM_READER
	    return GDBM_READER;
#else
	    goto not_there;
#endif
	if (strEQ(name, "GDBM_REPLACE"))
#ifdef GDBM_REPLACE
	    return GDBM_REPLACE;
#else
	    goto not_there;
#endif
	if (strEQ(name, "GDBM_WRCREAT"))
#ifdef GDBM_WRCREAT
	    return GDBM_WRCREAT;
#else
	    goto not_there;
#endif
	if (strEQ(name, "GDBM_WRITER"))
#ifdef GDBM_WRITER
	    return GDBM_WRITER;
#else
	    goto not_there;
#endif
	break;
    case 'H':
	break;
    case 'I':
	break;
    case 'J':
	break;
    case 'K':
	break;
    case 'L':
	break;
    case 'M':
	break;
    case 'N':
	break;
    case 'O':
	break;
    case 'P':
	break;
    case 'Q':
	break;
    case 'R':
	break;
    case 'S':
	break;
    case 'T':
	break;
    case 'U':
	break;
    case 'V':
	break;
    case 'W':
	break;
    case 'X':
	break;
    case 'Y':
	break;
    case 'Z':
	break;
    }
    errno = EINVAL;
    return 0;

not_there:
    errno = ENOENT;
    return 0;
}

#line 215 "GDBM_File.c"
XS(XS_GDBM_File_constant)
{
    dXSARGS;
    if (items != 2)
	Perl_croak(aTHX_ "Usage: GDBM_File::constant(name, arg)");
    {
	char *	name = (char *)SvPV(ST(0),PL_na);
	int	arg = (int)SvIV(ST(1));
	double	RETVAL;
	dXSTARG;

	RETVAL = constant(name, arg);
	XSprePUSH; PUSHn((double)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_GDBM_File_TIEHASH)
{
    dXSARGS;
    if (items < 4 || items > 5)
	Perl_croak(aTHX_ "Usage: GDBM_File::TIEHASH(dbtype, name, read_write, mode, fatal_func = (FATALFUNC)croak)");
    {
	char *	dbtype = (char *)SvPV(ST(0),PL_na);
	char *	name = (char *)SvPV(ST(1),PL_na);
	int	read_write = (int)SvIV(ST(2));
	int	mode = (int)SvIV(ST(3));
	FATALFUNC	fatal_func;
	GDBM_File	RETVAL;

	if (items < 5)
	    fatal_func = (FATALFUNC)croak;
	else {
	    fatal_func = (FATALFUNC)SvPV(ST(4),PL_na);
	}
#line 221 "GDBM_File.xs"
	{
	    GDBM_FILE  	dbp ;

	    RETVAL = NULL ;
	    if ((dbp =  gdbm_open(name, GDBM_BLOCKSIZE, read_write, mode, fatal_func))) {
	        RETVAL = (GDBM_File)safemalloc(sizeof(GDBM_File_type)) ;
    	        Zero(RETVAL, 1, GDBM_File_type) ;
		RETVAL->dbp = dbp ;
	    }

	}
#line 263 "GDBM_File.c"
	ST(0) = sv_newmortal();
        sv_setref_pv(ST(0), dbtype, (void*)RETVAL);
    }
    XSRETURN(1);
}

#define gdbm_close(db)			gdbm_close(db->dbp)
XS(XS_GDBM_File_close)
{
    dXSARGS;
    if (items != 1)
	Perl_croak(aTHX_ "Usage: GDBM_File::close(db)");
    {
	GDBM_File	db;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");

	gdbm_close(db);
#line 240 "GDBM_File.xs"
#line 288 "GDBM_File.c"
    }
    XSRETURN_EMPTY;
}

XS(XS_GDBM_File_DESTROY)
{
    dXSARGS;
    if (items != 1)
	Perl_croak(aTHX_ "Usage: GDBM_File::DESTROY(db)");
    {
	GDBM_File	db;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not a reference");
#line 246 "GDBM_File.xs"
	gdbm_close(db);
	safefree(db);
#line 310 "GDBM_File.c"
    }
    XSRETURN_EMPTY;
}

#define gdbm_FETCH(db,key)			gdbm_fetch(db->dbp,key)
XS(XS_GDBM_File_FETCH)
{
    dXSARGS;
    if (items != 2)
	Perl_croak(aTHX_ "Usage: GDBM_File::FETCH(db, key)");
    {
	GDBM_File	db;
	datum_key	key;
	datum_value	RETVAL;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");

	ckFilter(ST(1), filter_store_key, "filter_store_key");
	key.dptr = SvPV(ST(1), PL_na);
	key.dsize = (int)PL_na;;

	RETVAL = gdbm_FETCH(db, key);
	ST(0) = sv_newmortal();
	output_datum(aTHX_ ST(0), RETVAL.dptr, RETVAL.dsize);
	ckFilter(ST(0), filter_fetch_value,"filter_fetch_value");
    }
    XSRETURN(1);
}

#define gdbm_STORE(db,key,value,flags)		gdbm_store(db->dbp,key,value,flags)
XS(XS_GDBM_File_STORE)
{
    dXSARGS;
    if (items < 3 || items > 4)
	Perl_croak(aTHX_ "Usage: GDBM_File::STORE(db, key, value, flags = GDBM_REPLACE)");
    {
	GDBM_File	db;
	datum_key	key;
	datum_value	value;
	int	flags;
	int	RETVAL;
	dXSTARG;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");

	ckFilter(ST(1), filter_store_key, "filter_store_key");
	key.dptr = SvPV(ST(1), PL_na);
	key.dsize = (int)PL_na;;

        ckFilter(ST(2), filter_store_value, "filter_store_value");
	if (SvOK(ST(2))) {
	    value.dptr = SvPV(ST(2), PL_na);
	    value.dsize = (int)PL_na;
	}
	else {
	    value.dptr = "";
	    value.dsize = 0;
	};

	if (items < 4)
	    flags = GDBM_REPLACE;
	else {
	    flags = (int)SvIV(ST(3));
	}

	RETVAL = gdbm_STORE(db, key, value, flags);
	XSprePUSH; PUSHi((IV)RETVAL);
#line 263 "GDBM_File.xs"
	if (RETVAL) {
	    if (RETVAL < 0 && errno == EPERM)
		croak("No write permission to gdbm file");
	    croak("gdbm store returned %d, errno %d, key \"%.*s\"",
			RETVAL,errno,key.dsize,key.dptr);
	}
#line 395 "GDBM_File.c"
    }
    XSRETURN(1);
}

#define gdbm_DELETE(db,key)			gdbm_delete(db->dbp,key)
XS(XS_GDBM_File_DELETE)
{
    dXSARGS;
    if (items != 2)
	Perl_croak(aTHX_ "Usage: GDBM_File::DELETE(db, key)");
    {
	GDBM_File	db;
	datum_key	key;
	int	RETVAL;
	dXSTARG;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");

	ckFilter(ST(1), filter_store_key, "filter_store_key");
	key.dptr = SvPV(ST(1), PL_na);
	key.dsize = (int)PL_na;;

	RETVAL = gdbm_DELETE(db, key);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}

#define gdbm_FIRSTKEY(db)			gdbm_firstkey(db->dbp)
XS(XS_GDBM_File_FIRSTKEY)
{
    dXSARGS;
    if (items != 1)
	Perl_croak(aTHX_ "Usage: GDBM_File::FIRSTKEY(db)");
    {
	GDBM_File	db;
	datum_key	RETVAL;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");

	RETVAL = gdbm_FIRSTKEY(db);
	ST(0) = sv_newmortal();
	output_datum(aTHX_ ST(0), RETVAL.dptr, RETVAL.dsize);
	ckFilter(ST(0), filter_fetch_key,"filter_fetch_key");
    }
    XSRETURN(1);
}

#define gdbm_NEXTKEY(db,key)			gdbm_nextkey(db->dbp,key)
XS(XS_GDBM_File_NEXTKEY)
{
    dXSARGS;
    if (items != 2)
	Perl_croak(aTHX_ "Usage: GDBM_File::NEXTKEY(db, key)");
    {
	GDBM_File	db;
	datum_key	key;
	datum_key	RETVAL;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");

	ckFilter(ST(1), filter_store_key, "filter_store_key");
	key.dptr = SvPV(ST(1), PL_na);
	key.dsize = (int)PL_na;;

	RETVAL = gdbm_NEXTKEY(db, key);
	ST(0) = sv_newmortal();
	output_datum(aTHX_ ST(0), RETVAL.dptr, RETVAL.dsize);
	ckFilter(ST(0), filter_fetch_key,"filter_fetch_key");
    }
    XSRETURN(1);
}

#define gdbm_reorganize(db)			gdbm_reorganize(db->dbp)
XS(XS_GDBM_File_reorganize)
{
    dXSARGS;
    if (items != 1)
	Perl_croak(aTHX_ "Usage: GDBM_File::reorganize(db)");
    {
	GDBM_File	db;
	int	RETVAL;
	dXSTARG;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");

	RETVAL = gdbm_reorganize(db);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}

#define gdbm_sync(db)				gdbm_sync(db->dbp)
XS(XS_GDBM_File_sync)
{
    dXSARGS;
    if (items != 1)
	Perl_croak(aTHX_ "Usage: GDBM_File::sync(db)");
    {
	GDBM_File	db;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");

	gdbm_sync(db);
    }
    XSRETURN_EMPTY;
}

#define gdbm_EXISTS(db,key)			gdbm_exists(db->dbp,key)
XS(XS_GDBM_File_EXISTS)
{
    dXSARGS;
    if (items != 2)
	Perl_croak(aTHX_ "Usage: GDBM_File::EXISTS(db, key)");
    {
	GDBM_File	db;
	datum_key	key;
	int	RETVAL;
	dXSTARG;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");

	ckFilter(ST(1), filter_store_key, "filter_store_key");
	key.dptr = SvPV(ST(1), PL_na);
	key.dsize = (int)PL_na;;

	RETVAL = gdbm_EXISTS(db, key);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}

#define gdbm_setopt(db,optflag, optval, optlen)	gdbm_setopt(db->dbp,optflag, optval, optlen)
XS(XS_GDBM_File_setopt)
{
    dXSARGS;
    if (items != 4)
	Perl_croak(aTHX_ "Usage: GDBM_File::setopt(db, optflag, optval, optlen)");
    {
	GDBM_File	db;
	int	optflag = (int)SvIV(ST(1));
	int	optval = (int)SvIV(ST(2));
	int	optlen = (int)SvIV(ST(3));
	int	RETVAL;
	dXSTARG;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");

	RETVAL = gdbm_setopt(db, optflag, &optval, optlen);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}

#define setFilter(type)					\
	{						\
	    if (db->type)				\
	        RETVAL = sv_mortalcopy(db->type) ; 	\
	    ST(0) = RETVAL ;				\
	    if (db->type && (code == &PL_sv_undef)) {	\
                SvREFCNT_dec(db->type) ;		\
	        db->type = NULL ;			\
	    }						\
	    else if (code) {				\
	        if (db->type)				\
	            sv_setsv(db->type, code) ;		\
	        else					\
	            db->type = newSVsv(code) ;		\
	    }	    					\
	}
XS(XS_GDBM_File_filter_fetch_key)
{
    dXSARGS;
    if (items != 2)
	Perl_croak(aTHX_ "Usage: GDBM_File::filter_fetch_key(db, code)");
    {
	GDBM_File	db;
	SV *	code = ST(1);
	SV *	RETVAL = &PL_sv_undef ;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");
#line 338 "GDBM_File.xs"
	    setFilter(filter_fetch_key) ;
#line 619 "GDBM_File.c"
    }
    XSRETURN(1);
}

XS(XS_GDBM_File_filter_store_key)
{
    dXSARGS;
    if (items != 2)
	Perl_croak(aTHX_ "Usage: GDBM_File::filter_store_key(db, code)");
    {
	GDBM_File	db;
	SV *	code = ST(1);
	SV *	RETVAL =  &PL_sv_undef ;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");
#line 346 "GDBM_File.xs"
	    setFilter(filter_store_key) ;
#line 642 "GDBM_File.c"
    }
    XSRETURN(1);
}

XS(XS_GDBM_File_filter_fetch_value)
{
    dXSARGS;
    if (items != 2)
	Perl_croak(aTHX_ "Usage: GDBM_File::filter_fetch_value(db, code)");
    {
	GDBM_File	db;
	SV *	code = ST(1);
	SV *	RETVAL =  &PL_sv_undef ;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");
#line 354 "GDBM_File.xs"
	    setFilter(filter_fetch_value) ;
#line 665 "GDBM_File.c"
    }
    XSRETURN(1);
}

XS(XS_GDBM_File_filter_store_value)
{
    dXSARGS;
    if (items != 2)
	Perl_croak(aTHX_ "Usage: GDBM_File::filter_store_value(db, code)");
    {
	GDBM_File	db;
	SV *	code = ST(1);
	SV *	RETVAL =  &PL_sv_undef ;

	if (sv_derived_from(ST(0), "GDBM_File")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    db = INT2PTR(GDBM_File,tmp);
	}
	else
	    croak("db is not of type GDBM_File");
#line 362 "GDBM_File.xs"
	    setFilter(filter_store_value) ;
#line 688 "GDBM_File.c"
    }
    XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_GDBM_File)
{
    dXSARGS;
    char* file = __FILE__;

    XS_VERSION_BOOTCHECK ;

        newXS("GDBM_File::constant", XS_GDBM_File_constant, file);
        newXS("GDBM_File::TIEHASH", XS_GDBM_File_TIEHASH, file);
        newXS("GDBM_File::close", XS_GDBM_File_close, file);
        newXS("GDBM_File::DESTROY", XS_GDBM_File_DESTROY, file);
        newXS("GDBM_File::FETCH", XS_GDBM_File_FETCH, file);
        newXS("GDBM_File::STORE", XS_GDBM_File_STORE, file);
        newXS("GDBM_File::DELETE", XS_GDBM_File_DELETE, file);
        newXS("GDBM_File::FIRSTKEY", XS_GDBM_File_FIRSTKEY, file);
        newXS("GDBM_File::NEXTKEY", XS_GDBM_File_NEXTKEY, file);
        newXS("GDBM_File::reorganize", XS_GDBM_File_reorganize, file);
        newXS("GDBM_File::sync", XS_GDBM_File_sync, file);
        newXS("GDBM_File::EXISTS", XS_GDBM_File_EXISTS, file);
        newXS("GDBM_File::setopt", XS_GDBM_File_setopt, file);
        newXS("GDBM_File::filter_fetch_key", XS_GDBM_File_filter_fetch_key, file);
        newXS("GDBM_File::filter_store_key", XS_GDBM_File_filter_store_key, file);
        newXS("GDBM_File::filter_fetch_value", XS_GDBM_File_filter_fetch_value, file);
        newXS("GDBM_File::filter_store_value", XS_GDBM_File_filter_store_value, file);
    XSRETURN_YES;
}

