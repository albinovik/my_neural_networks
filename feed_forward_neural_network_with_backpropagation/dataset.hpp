#ifndef _DATASET_HPP_
#define _DATASET_HPP_


class Dataset
{
private:
    Image *data;
    int size;
public:
    //Dataset();//for mnisr dataset
    Dataset(string filename);
    Dataset(string filename, char mode);
    ~Dataset();
    int GetSize();
    double GetElement(int i);
    double GetPixel(int i, int j);
    double *GetPixelLayer(int i);
};



#endif