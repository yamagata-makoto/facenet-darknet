#include "darknet.h"

static network *net;

void init_net
    (
    const char *cfgfile,
    const char *weightfile,
    int *inw,
    int *inh,
    int *outc
    )
{
    net = load_network_custom(cfgfile, weightfile, 0, 1);
    *inw = net->w;
    *inh = net->h;
    *outc = net->layers[net->n - 1].out_c;

    nnp_initialize();
}

float *run_net
    (
    float *indata
    )
{
    network_predict_ptr(net, indata);
    return net->output;
}

void free_net
    (
    void
    )
{
    free_network(*net);
    free(net);

    nnp_deinitialize();
}
