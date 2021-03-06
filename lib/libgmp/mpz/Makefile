
.EXPORT_ALL_VARIABLES:

#VPATH = $(ROOTDIR)/freeswan/gmp/mpz
CFLAGS += -I../../$(LIBCDIR)/include
srcdir = $(ROOTDIR)/lib/libgmp/mpz

MPZ_SRCS = \
	abs.c add.c add_ui.c addmul_ui.c and.c array_init.c \
	bin_ui.c bin_uiui.c cdiv_q.c \
	cdiv_q_ui.c cdiv_qr.c cdiv_qr_ui.c cdiv_r.c cdiv_r_ui.c cdiv_ui.c \
	clear.c clrbit.c cmp.c cmp_si.c cmp_ui.c cmpabs.c cmpabs_ui.c com.c \
	divexact.c dump.c fac_ui.c fdiv_q.c fdiv_q_2exp.c fdiv_q_ui.c \
	fdiv_qr.c fdiv_qr_ui.c fdiv_r.c fdiv_r_2exp.c fdiv_r_ui.c fdiv_ui.c \
	fib_ui.c fits_sint_p.c fits_slong_p.c fits_sshort_p.c fits_uint_p.c \
	fits_ulong_p.c fits_ushort_p.c gcd.c gcd_ui.c gcdext.c get_d.c get_si.c \
	get_str.c get_ui.c getlimbn.c hamdist.c init.c inp_raw.c inp_str.c \
	invert.c ior.c iset.c iset_d.c iset_si.c iset_str.c iset_ui.c \
	jacobi.c lcm.c legendre.c mod.c mul.c mul_2exp.c mul_ui.c neg.c nextprime.c \
	out_raw.c out_str.c perfpow.c perfsqr.c popcount.c pow_ui.c powm.c \
	powm_ui.c pprime_p.c random.c random2.c realloc.c remove.c root.c rrandomb.c \
	scan0.c scan1.c set.c set_d.c set_f.c set_q.c set_si.c set_str.c \
	set_ui.c setbit.c size.c sizeinbase.c sqrt.c sqrtrem.c sub.c \
	sub_ui.c swap.c tdiv_ui.c tdiv_q.c tdiv_q_2exp.c tdiv_q_ui.c tdiv_qr.c \
	tdiv_qr_ui.c tdiv_r.c tdiv_r_2exp.c tdiv_r_ui.c tstbit.c ui_pow_ui.c \
	urandomb.c urandomm.c xor.c
MPZ_OBJS = \
	abs.o add.o add_ui.o addmul_ui.o and.o \
	array_init.o bin_ui.o bin_uiui.o cdiv_q.o cdiv_q_ui.o cdiv_qr.o \
	cdiv_qr_ui.o cdiv_r.o cdiv_r_ui.o cdiv_ui.o clear.o clrbit.o \
	cmp.o cmp_si.o cmp_ui.o cmpabs.o cmpabs_ui.o com.o divexact.o \
	dump.o fac_ui.o fdiv_q.o fdiv_q_2exp.o fdiv_q_ui.o fdiv_qr.o \
	fdiv_qr_ui.o fdiv_r.o fdiv_r_2exp.o fdiv_r_ui.o fdiv_ui.o \
	fib_ui.o fits_sint_p.o fits_slong_p.o fits_sshort_p.o \
	fits_uint_p.o fits_ulong_p.o fits_ushort_p.o gcd.o gcd_ui.o \
	gcdext.o get_d.o get_si.o get_str.o get_ui.o getlimbn.o \
	hamdist.o init.o inp_raw.o inp_str.o invert.o ior.o iset.o \
	iset_d.o iset_si.o iset_str.o iset_ui.o jacobi.o lcm.o \
	legendre.o mod.o mul.o mul_2exp.o mul_ui.o neg.o nextprime.o \
	out_raw.o out_str.o perfpow.o perfsqr.o popcount.o pow_ui.o \
	powm.o powm_ui.o pprime_p.o random.o random2.o realloc.o \
	remove.o root.o rrandomb.o scan0.o scan1.o set.o set_d.o \
	set_f.o set_q.o set_si.o set_str.o set_ui.o setbit.o size.o \
	sizeinbase.o sqrt.o sqrtrem.o sub.o sub_ui.o swap.o tdiv_ui.o \
	tdiv_q.o tdiv_q_2exp.o tdiv_q_ui.o tdiv_qr.o tdiv_qr_ui.o \
	tdiv_r.o tdiv_r_2exp.o tdiv_r_ui.o tstbit.o ui_pow_ui.o \
	urandomb.o urandomm.o xor.o

INCLUDES = -I. -I.. -I../mpn -I$(srcdir)/..

CFLAGS += $(INCLUDES)

libmpz.a: Makefile $(MPZ_OBJS)
	rm -f $@
	$(AR) cr $@ $(MPZ_OBJS)

.PHONY: clean

clean:
	rm -f *.o libmpz.a

H = $(srcdir)/../gmp.h $(srcdir)/../gmp-impl.h ../mpn/gmp-mparam.h

abs.o: $(srcdir)/abs.c $(H)
add.o: $(srcdir)/add.c $(H)
add_ui.o: $(srcdir)/add_ui.c $(H)
and.o: $(srcdir)/and.c $(H)
array_init.o: $(srcdir)/array_init.c $(H)
cdiv_q.o: $(srcdir)/cdiv_q.c $(H)
cdiv_q_ui.o: $(srcdir)/cdiv_q_ui.c $(H)
cdiv_qr.o: $(srcdir)/cdiv_qr.c $(H)
cdiv_qr_ui.o: $(srcdir)/cdiv_qr_ui.c $(H)
cdiv_r.o: $(srcdir)/cdiv_r.c $(H)
cdiv_r_ui.o: $(srcdir)/cdiv_r_ui.c $(H)
cdiv_ui.o: $(srcdir)/cdiv_ui.c $(H)
clear.o: $(srcdir)/clear.c $(H)
clrbit.o: $(srcdir)/clrbit.c $(H)
cmp.o: $(srcdir)/cmp.c $(H)
cmp_si.o: $(srcdir)/cmp_si.c $(H)
cmp_ui.o: $(srcdir)/cmp_ui.c $(H)
com.o: $(srcdir)/com.c $(H)
fdiv_q_2exp.o: $(srcdir)/fdiv_q_2exp.c $(H)
fdiv_r_2exp.o: $(srcdir)/fdiv_r_2exp.c $(H)
divexact.o: $(srcdir)/divexact.c $(H) $(srcdir)/../longlong.h
fac_ui.o: $(srcdir)/fac_ui.c $(H) $(srcdir)/../longlong.h
fdiv_q.o: $(srcdir)/fdiv_q.c $(H)
fdiv_q_ui.o: $(srcdir)/fdiv_q_ui.c $(H)
fdiv_qr.o: $(srcdir)/fdiv_qr.c $(H)
fdiv_qr_ui.o: $(srcdir)/fdiv_qr_ui.c $(H)
fdiv_r.o: $(srcdir)/fdiv_r.c $(H)
fdiv_r_ui.o: $(srcdir)/fdiv_r_ui.c $(H)
fdiv_ui.o: $(srcdir)/fdiv_ui.c $(H)
gcd.o: $(srcdir)/gcd.c $(H) $(srcdir)/../longlong.h
gcd_ui.o: $(srcdir)/gcd_ui.c $(H)
gcdext.o: $(srcdir)/gcdext.c $(H)
get_d.o: $(srcdir)/get_d.c $(H)
get_si.o: $(srcdir)/get_si.c $(H)
get_str.o: $(srcdir)/get_str.c $(H)
get_ui.o: $(srcdir)/get_ui.c $(H)
getlimbn.o: $(srcdir)/getlimbn.c $(H)
hamdist.o: $(srcdir)/hamdist.c $(H)
init.o: $(srcdir)/init.c $(H)
inp_raw.o: $(srcdir)/inp_raw.c $(H)
inp_str.o: $(srcdir)/inp_str.c $(H)
invert.o: $(srcdir)/invert.c $(H)
ior.o: $(srcdir)/ior.c $(H)
iset.o: $(srcdir)/iset.c $(H)
iset_d.o: $(srcdir)/iset_d.c $(H)
iset_si.o: $(srcdir)/iset_si.c $(H)
iset_str.o: $(srcdir)/iset_str.c $(H)
iset_ui.o: $(srcdir)/iset_ui.c $(H)
jacobi.o: $(srcdir)/jacobi.c $(H)
legendre.o: $(srcdir)/legendre.c $(H)
mod.o: $(srcdir)/mod.c $(H)
tdiv_q_2exp.o: $(srcdir)/tdiv_q_2exp.c $(H)
tdiv_r_2exp.o: $(srcdir)/tdiv_r_2exp.c $(H)
mul.o: $(srcdir)/mul.c $(H)
mul_2exp.o: $(srcdir)/mul_2exp.c $(H)
mul_ui.o: $(srcdir)/mul_ui.c $(H)
neg.o: $(srcdir)/neg.c $(H)
out_raw.o: $(srcdir)/out_raw.c $(H)
out_str.o: $(srcdir)/out_str.c $(H)
perfsqr.o: $(srcdir)/perfsqr.c $(H)
popcount.o: $(srcdir)/popcount.c $(H)
pow_ui.o: $(srcdir)/pow_ui.c $(H) $(srcdir)/../longlong.h
powm.o: $(srcdir)/powm.c $(H) $(srcdir)/../longlong.h
powm_ui.o: $(srcdir)/powm_ui.c $(H) $(srcdir)/../longlong.h
pprime_p.o: $(srcdir)/pprime_p.c $(H)
random.o: $(srcdir)/random.c $(H) $(srcdir)/../urandom.h
random2.o: $(srcdir)/random2.c $(H)
realloc.o: $(srcdir)/realloc.c $(H)
scan0.o: $(srcdir)/scan0.c $(H)
scan1.o: $(srcdir)/scan1.c $(H)
set.o: $(srcdir)/set.c $(H)
set_d.o: $(srcdir)/set_d.c $(H)
set_f.o: $(srcdir)/set_f.c $(H)
set_q.o: $(srcdir)/set_q.c $(H)
set_si.o: $(srcdir)/set_si.c $(H)
set_str.o: $(srcdir)/set_str.c $(H) $(srcdir)/../longlong.h
set_ui.o: $(srcdir)/set_ui.c $(H)
setbit.o: $(srcdir)/setbit.c $(H)
size.o: $(srcdir)/size.c $(H)
sizeinbase.o: $(srcdir)/sizeinbase.c $(H) $(srcdir)/../longlong.h
sqrt.o: $(srcdir)/sqrt.c $(H)
sqrtrem.o: $(srcdir)/sqrtrem.c $(H)
sub.o: $(srcdir)/sub.c $(H)
sub_ui.o: $(srcdir)/sub_ui.c $(H)
tdiv_q.o: $(srcdir)/tdiv_q.c $(H) $(srcdir)/../longlong.h
tdiv_q_ui.o: $(srcdir)/tdiv_q_ui.c $(H)
tdiv_qr.o: $(srcdir)/tdiv_qr.c $(H) $(srcdir)/../longlong.h $(H)
tdiv_qr_ui.o: $(srcdir)/tdiv_qr_ui.c $(H)
tdiv_r.o: $(srcdir)/tdiv_r.c $(H) $(srcdir)/../longlong.h $(H)
tdiv_r_ui.o: $(srcdir)/tdiv_r_ui.c $(H)
ui_pow_ui.o: $(srcdir)/ui_pow_ui.c $(H) $(srcdir)/../longlong.h

