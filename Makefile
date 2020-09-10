WCC386=wcc386
WLINK=wlink

CFLAGS=-q -i=sos/include -bt=dos4g
CFLAGS3=-q -i=sos3/include -bt=dos4g
LFLAGS=option quiet

all: sosplay.exe sosplay3.exe

clean:
	rm -f sosplay.o
	rm -f sosplay.exe
	rm -f hmimdrv.386

deploy:
	mkdir -p out
	cp sosplay.exe out
	cp dos4gw.exe out
	cp hmimdrv.386 out
	cp midi2hmi.exe out
	cp rickmelo.bnk out
	cp rickdrum.bnk out
	cp drum.bnk out
	cp maz.hmi out
	cp maz.bat out


#
# SOSPLAY executable
#

sosplay.exe: dos4gw.exe hmimdrv.386 sosplay.c
	$(WCC386) $(CFLAGS) -dDPMI sosplay.c
	$(WLINK) $(LFLAGS) n sosplay d all libp sos/lib libr sosw1cr f sosplay system dos4g

sosplay3.exe: dos4gw.exe hmimdrv.386 sosplay3.c
	$(WCC386) $(CFLAGS3) -dDPMI sosplay3.c
	$(WLINK) $(LFLAGS) n sosplay3 d all libp sos3/lib libr sosdw1cr,sosmw1cr f sosplay system dos4g

#
# DOS/4GW executable
#

dos4gw.exe:
	cp $(WATCOM)/binw/dos4gw.exe dos4gw.exe

#
# HMI MIDI Driver
#

hmimdrv.386:
	cp sos/drivers/hmimdrv.386 hmimdrv.386



.PHONY:
	clean
	deploy

