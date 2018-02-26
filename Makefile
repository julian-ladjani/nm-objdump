make:
	make -f ./Makefile.nm all
	make -f ./Makefile.objdump all

nm:
	make -f ./Makefile.nm re

objdump:
	make -f ./Makefile.objdump re

all:
	make -f ./Makefile.nm all
	make -f ./Makefile.objdump all

clean:
	make -f ./Makefile.nm clean
	make -f ./Makefile.objdump clean

fclean:
	make -f ./Makefile.nm fclean
	make -f ./Makefile.objdump fclean

re:
	make -f ./Makefile.nm re
	make -f ./Makefile.objdump re

.PHONY: all clean fclean re nm objdump

