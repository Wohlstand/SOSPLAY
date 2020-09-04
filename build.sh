export WATCOM=/opt/watcom
export EDPATH=$WATCOM/eddat
export WIPFC=$WATCOM/wipfc
export INCLUDE="$WATCOM/h"
#WATCOM_FLAGS="-q -bdos4g -march=i386"
#export CFLAGS="$WATCOM_FLAGS -xc -std=wc"
#export CXXFLAGS="$WATCOM_FLAGS -xc++ -xs -feh -frtti -std=c++98"
export LFLAGS="$WATCOM_FLAGS"

export PATH=$WATCOM/binl:$PATH

make -j 6

