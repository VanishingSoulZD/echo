OBJ = server client client_test \
      server.o sig_chld.o serv_do.o client.o cli_do.o client_test.o input_his.file output_his.file
OBJSERV = server.o sig_chld.o serv_do.o
OBJCLI = client.o cli_do.o
OBJCLITEST = client_test.o cli_do.o

all : server client client_test
.PHONY : all

server : $(OBJSERV)
	g++ -o server $(OBJSERV)

client : $(OBJCLI)
	g++ -o client $(OBJCLI)

client_test : $(OBJCLITEST)
	g++ -o client_test $(OBJCLITEST)

server.o : echo.h

sig_chld.o : echo.h

serv_do.o : echo.h

client.o : echo.h

cli_do.o : echo.h

client_test.o : echo.h

.PHONY : clean
clean :
	-rm $(OBJ)
