newsserver.o newsserver.d : newsserver.cc server.h ../shared/connection.h \
 ../shared/connectionclosedexception.h process.h database.h \
 ../shared/newsgroup.h ../shared/article.h ../shared/stream.h \
 ../shared/connection.h ../shared/invalidprotocolexception.h \
 servererrorexception.h
