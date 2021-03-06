#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class Combine2images
{
private:
    FileStorage Settings_;

public:
    Combine2images(FileStorage Settings);
    int combine_rgb_depth();
    int combine_image_mask();
    ~Combine2images();
};

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "missing config, argc: " << argc << endl;
        exit(1);
    }
    string yaml_path = argv[1];
    FileStorage Settings(yaml_path, FileStorage::READ);
    Combine2images *combiner = new Combine2images(Settings);
    string combineStyle = Settings["combineStyle"];
    cout << "combineStyle " << combineStyle << endl;
    if (!combineStyle.compare("rgb_depth"))
    {
        combiner->combine_rgb_depth();
    }
    else if (!combineStyle.compare("image_mask"))
    {
        combiner->combine_image_mask();
    }
    else
    {
        cout << "wrong style!" << endl;
        exit(-1);
    }

    return 0;
}

Combine2images::Combine2images(FileStorage Settings) : Settings_(Settings)
{
}

Combine2images::~Combine2images()
{
}
int Combine2images::combine_rgb_depth()
{

    return 0;
}
int Combine2images::combine_image_mask()
{
    int mask_alpha = Settings_["mask_alpha"];
    Mat image_mask = imread(Settings_["mask_path"], -1);
    cout << "image_mask.empty() " << image_mask.empty() << image_mask.type() << endl;
    // cout << "image_in.empty() " << image_in.empty() << image_in.cols << endl;
    vector<int> mask_value;
    Settings_["mask_value"] >> mask_value;

    // typedef cv::Point3_<uint8_t> Pixel;
    typedef uint8_t Pixel;
    image_mask.forEach<Pixel>([&](Pixel &pixel, const int position[]) -> void {
        if (std::find(mask_value.begin(), mask_value.end(), pixel) != mask_value.end())
        {
            pixel = 0;
        }
        else
        {
            pixel = 255;
        }
    });
    string mask_out_path(Settings_["mask_out_path"]);
    cout << mask_out_path << endl;
    imwrite(mask_out_path, image_mask);

    int if_save_rgb_mask = Settings_["save_rgb_mask"];
    if (if_save_rgb_mask)
    {
        Mat image_out;
        Mat image_in = imread(Settings_["image_path"], -1);
        image_in.copyTo(image_out, image_mask);
        string image_out_path(Settings_["image_out_path"]);
        cout << image_out_path << endl;
        imwrite(image_out_path, image_out);
    }

    int if_save_erode_mask = Settings_["save_erode_mask"];
    if (if_save_erode_mask)
    {
        int erode_mask_kernel = Settings_["erode_mask_kernel"];
        cv::erode(image_mask, image_mask, Mat(erode_mask_kernel, erode_mask_kernel, CV_8UC1, 1));

        string image_out_path(Settings_["mask_erode_out"]);
        cout << image_out_path << endl;
        imwrite(image_out_path, image_mask);
    }
    if (if_save_rgb_mask)
    {
        Mat image_out;
        Mat image_in = imread(Settings_["image_path"], -1);
        image_in.copyTo(image_out, image_mask);
        string image_out_path(Settings_["image_erode_out"]);
        cout << image_out_path << endl;
        imwrite(image_out_path, image_out);
    }
    return 0;
}