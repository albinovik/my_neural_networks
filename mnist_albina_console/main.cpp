#include <QCoreApplication>
#include <QFile>
#include <QtGui/QImage>
#include <dirent.h>
#include <random>

/*

  You should prepare files with specific names.
  The name of the file should has first symbol according file contents.
  For example, if the file is keeping an image of letter A,
  you should to name your file in one of the following ways:

  A.png   a.png   A1.png   Aa2.png    alpha.png   ...   and so on.

  Also, you should change name of directory with images if it is necessary.
  You have to check all pathes in code before using.

*/

using namespace std;

void write_to_file_pixels(QString path, QString filename, int number)
{
    //opening a text file for pixels writing
    QFile mFile("E:\\C++ projects\\Qt_projects\\mnist_format_prepare\\test.txt");
    mFile.open(QIODevice::Append);
    QTextStream fin(&mFile);
    fin.setRealNumberPrecision(3);

    //extracting of first symbol from the name of an image file
    QString change_mark = filename[0].toUpper();
    //qDebug() << filename[0] << Qt::endl;
    //qDebug() << change_mark << Qt::endl;
    fin << "Examples " << number << Qt::endl;//writing number of image examples
    fin << change_mark << Qt::endl;//writing symbol in text file before pixels

    //creating image from the image file
    QImage img;
    img.load(path, "PNG");

    //change scale for pixels
    img = img.scaledToHeight(28);
    img = img.scaledToWidth(28);
    //int pixWidth = img.width();
    //int pixHeight = img.height();
    //qDebug() << pixWidth;
    //qDebug() << pixHeight;

    //writing pixels in the text file for each image file
    int w = img.size().width();
    int h = img.size().height();
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fin << 1.0 - img.pixelColor(j,i).green()/ 255. << " ";
        }
        fin << Qt::endl;
    }
    mFile.close();//close the file and return to main function
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<QString> FilenameKeep;
    QVector<QString> FilepathKeep;

    int count = 0;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("E:\\C++ projects\\Qt_projects\\mnist_format_prepare\\shapes")) != NULL) {
      /* read all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
        string temp = ent->d_name;
        QString temp2 = QString::fromStdString(temp);
        QString temp3 = "E:\\C++ projects\\Qt_projects\\mnist_format_prepare\\shapes\\" + temp2;
        //qDebug() << temp3 << Qt::endl;
        if(count >= 2)
        {
            FilenameKeep.push_back(temp2);
            FilepathKeep.push_back(temp3);
            //write_to_file_pixels(temp3, temp2);
        }
        count++;
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
      return EXIT_FAILURE;
    }


    //the files data is swapped randomly
    shuffle(FilenameKeep.begin(), FilenameKeep.end(), default_random_engine());
    shuffle(FilepathKeep.begin(), FilepathKeep.end(), default_random_engine());


    for(int i = 0; i < FilenameKeep.size(); i++)
    {
        write_to_file_pixels(FilepathKeep[i], FilenameKeep[i], count - 2);
        //qDebug() << "Filename: " << FilenameKeep[i] << ",  Filepath: " << FilepathKeep[i] << Qt::endl;
    }

    qDebug() << "Everything is done." << Qt::endl;

    //return a.exec();

    return 0;
}
