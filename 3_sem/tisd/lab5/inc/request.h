#ifndef REQUEST_H
#define REQUEST_H

typedef struct
{
    int cycles_left;
    double arrival_time;
    double processing_time;
} Request;

#endif//REQUEST_H
