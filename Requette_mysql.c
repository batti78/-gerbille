#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include "Bash.c"

int main(void)
{
  MYSQL mysql;
  mysql_init(&mysql);
  mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

  if(mysql_real_connect(&mysql, "localhost", "Kim", "gerbille", "elevage", 0, NULL, 0))
  {
    write();
    const char* requette = "LOAD DATA LOCAL INFILE 'dl_pic.cvs INTO TABLE Images [FIELDS [TERMINATED BY ';']] [LINES [TERMINATED BY '\n']] [(name, image)];";
    mysql_query(&mysql, requette);
    mysql_close(&mysql);
  }
  else
  {
    printf("Une erreur s'est produite lors de la connexion à la BDD !");
  }

  return 0;
}
