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
<<<<<<< HEAD
    Dataset(string filename, char mode);
=======
>>>>>>> cecdbdf57ff9bb8e4621578ed7e44b327c7b98f6
    ~Dataset();
    int GetSize();
    double GetElement(int i);
    double GetPixel(int i, int j);
    double *GetPixelLayer(int i);
};



#endif