#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# Foobar is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.
#

CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c89 -pedantic-errors -Og
#	-Og -march=native -mtune=native
PROGNAME=main
LIBS=-lz
OBJS=$(PROGNAME).o

.PHONY: all clean clean-all

all: $(PROGNAME)

$(PROGNAME): $(OBJS)
	$(CC) -o '$@' $^ $(LIBS)

$(PROGNAME).o: $(PROGNAME).c
	$(CC) -x c $(CFLAGS) -c -o '$@' '$<'

clean:
	-@rm $(OBJS)
clean-all: clean
	-@rm ./$(PROGNAME)

# ex: set filetype=make:
