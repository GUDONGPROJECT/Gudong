#ifndef _Show_HZ_H_
#define _Show_HZ_H_


//void get_16hz(FILE *hzk_p,char incode[],char bytes[]);
void dis_16hz(int x, int y, char *s, int color);

//void get_24hz(FILE *hzk_p,char incode[],char bytes[]);
void dis_24hz(int x, int y, char *s, int color);

//void get_16zf(FILE *hzk_p,char *s,char bytes[]);
void dis_16zf(int x0, int y0, char *s, int color);

//void get_24zf(FILE *hzk_p,char *s,char bytes[]);
void dis_24zf(int x0, int y0, char *s, int color);

void dis_16xh(int x0, int y0, int n, int color);

void dis_16srf(int x, int y, int qw, int n, int page, int color);

void dis_16srfhz(int x, int y, int qw, int n, int page, int color);

void dis_hz(int x, int y, int M, char *s, int color);

void dis_hz_gai(int x, int y, int M, char *s, int color);

void dis_16hz_gai(int x0, int y0, char *s, int color, int n);

void dis_24hz_gai(int x0, int y0, char *s, int color, int n);

#endif
