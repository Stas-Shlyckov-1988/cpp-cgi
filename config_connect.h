#ifndef CONFIG_CONNECT_H
#define CONFIG_CONNECT_H
struct connection
{
    unsigned port = 3306;
    const char *host = "localhost";
	const char *user = "mpeegy";
	const char *password = "procedure";
	const char *dbname = "test";
};
#endif