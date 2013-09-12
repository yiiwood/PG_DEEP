//**********************
// lipiji.sdu@gmail.com
// 2013-06-25
//*********************/ 
#include "deep.h"
int main(int argc, const char *argv[])
{
    string ftx = "./data/x.txt";
    string fty = "./data/y.txt";
    int epoch = 500;
    int batch_size = 0;
    double gamma = 0.1; // learning rate
    int k = 1; //Contrastive Divergence k

    int hls[] = {400, 400, 100};
    int n_layers = sizeof(hls) / sizeof(hls[0]);
    int n_lables = 2;

    Conf conf(ftx, fty, epoch, batch_size, hls, k, gamma, n_layers, n_lables);
    Dataset data(conf);

    /* test rbm
       RBM rbm(data.N, data.n_f, conf.n_h, NULL, NULL, NULL);

       for(int i=0; i<epoch; i++)
       {
       cout << "epoch: " << i << endl;
       for(int j=0; j<data.N; j++)
       rbm.train(data.X[j], gamma, k);

       ofstream fout("./model/W.txt");
       for(int j=0; j<rbm.n_visible; j++)
       {
       for(int l=0; l<rbm.n_hidden; l++)
       {
       fout << rbm.W[l][j] << " ";
       }
       fout << endl;
       }
       fout << flush;
       fout.close();


       }*/	

    //test lr
    LR lr(data, conf);
    for(int i=0; i<epoch; i++)
    {
        cout << "epoch: " << i << endl;
        for(int j=0; j<data.N; j++)
        {
            double *x = new double[lr.n_features];
            for(int f=0; f<lr.n_features; f++)
                x[f] = data.X[j][f];
            int *y = new int[lr.n_labels];
            y[int(data.Y[j])] = 1;

            lr.train(x, y, gamma);
        }
    }
    for(int j=0; j<data.N; j++)
    {
        double *x = new double[lr.n_features];
        for(int f=0; f<lr.n_features; f++)
            x[f] = data.X[j][f];
        double *y = new double[lr.n_labels];

        lr.predict(x, y);
        cout <<data.Y[j]<<": ";
        for(int i=0; i<lr.n_labels; i++)
            cout <<y[i]<<" ";
        cout<<endl;
        delete[] y;
    }
    /*DBN dbn(data, conf);
      dbn.pretrain(data, conf);
      for(int i=0; i<n_layers; i++)
      {
      char str[] = "./model/W";
      char W_l[128];
      sprintf(W_l, "%s%d", str, (i+1));

      ofstream fout(W_l);
      for(int j=0; j<dbn.rbm_layers[i]->n_visible; j++)
      {
      for(int l=0; l<dbn.rbm_layers[i]->n_hidden; l++)
      {
      fout << dbn.rbm_layers[i]->W[l][j] << " ";
      }
      fout << endl;
      }
      fout << flush;
      fout.close();

      }*/

    return 0;
}