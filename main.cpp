//TO DO
// MAKE/USE HELPER FUNCTIONS
//COMMENT
//INDENT
//README
//UNCOMPRESS

#include <cstdlib>
#include <cmath>
#include <map>
#include <set>
#include "image.h"
// ===================================================================================================
// ===================================================================================================
using namespace std;
typedef map<pair<int,int>, pair<set<pair<int,int> >,bool> >  MAP;

bool validHashInsertion(const int & offsetx, const int & offsety, const MAP::iterator & itr, Image<Color> & hash_data, const Image<Color> & input) {
    for(set<pair<int,int> >::iterator hashitr = ((itr->second).first).begin(); hashitr != ((itr->second).first).end(); hashitr++) {
        int x = (hashitr->first + offsetx) % hash_data.Width(); //might need to make it outside for both of these
        int y =	(hashitr->second  + offsety) % hash_data.Height();
        if (x < 0 || y < 0 || x > hash_data.Width() - 1 || y > hash_data.Height() - 1 || (!hash_data.GetPixel(x,y).isWhite())) {
            return false;
        }
    }

    for(set<pair<int,int> >::iterator hashitr = (itr->second.first).begin(); hashitr != (itr->second.first).end(); hashitr++) {

        int x = (hashitr->first + offsetx) % hash_data.Width() ;
        int y =	(hashitr->second  + offsety) % hash_data.Height();

        assert(hash_data.GetPixel(x,y).isWhite());
        hash_data.SetPixel(x,y,input.GetPixel((hashitr->first),(hashitr->second)));
    }

    return true;
}

void allocateoffset(const int & count, int & preset, Image<Offset> & offset) {
    int modifier = preset;
//better efficiency to sqrt that again
    for (int i = 2; i < (int)floor(sqrt(count * 1.01)+.5); i++) {

        if (((int)floor(sqrt(count * 1.01)+.5) % i == 0 && (int)floor(sqrt(count/4)+.5 + modifier) % i == 0) ||  (int)floor(sqrt(count * 1.01)+.5) % (int)floor((sqrt(count/4)+.5) + modifier) == 0 ) {
            modifier++;
            i = 2;
        }

    }
    preset = modifier;
    offset.Allocate((int)floor(sqrt(count/4)+.5 + modifier),(int)floor(sqrt(count/4)+.5 + modifier));
}


void Compress(const Image<Color> &input,
              Image<bool> &occupancy, Image<Color> &hash_data, Image<Offset> &offset) {
    // occupancy.Allocate(input.Width(),input.Height());
    // MAP tempoffset;
    // int count = 0;
    // for (int i = 0; i < input.Width(); i++) {
    // for (int j = 0; j < input.Height(); j++) {

    // if (!input.GetPixel(i,j).isWhite()) {
    // occupancy.SetPixel(i,j,true);
    // count++;
    // }
    // else {
    // occupancy.SetPixel(i,j,false);
    // }

    // }
    // }



    // hash_data.Allocate((int)floor(sqrt(count * 1.01)+.5),(int)floor(sqrt(count * 1.01)+ .5));
    // int preset = 0;
    // allocateoffset(count,preset,offset);
    // for (int i = 0; i < input.Width(); i++) {

    // for (int j = 0; j < input.Height(); j++) {

    // if (!input.GetPixel(i,j).isWhite()) {


    // MAP::iterator p = tempoffset.find(make_pair(i % offset.Width(),j % offset.Height()));
    // if (p == tempoffset.end()) {
    // pair< set<pair<int,int> >,bool > temp;
    // set<pair<int,int> > tempcolor;
    // tempcolor.insert(make_pair(i,j));
    // temp = make_pair(tempcolor,true);
    // tempoffset.insert(make_pair(make_pair(i % offset.Width(),j % offset.Height()),temp));
    // }
    // else {
    // ((p)->second.first).insert(make_pair(i,j));
    // }
    // }

    // }

    // }



    // MAP::iterator next_biggest = tempoffset.end();
    // int max = -1;
    // MAP::iterator itr = tempoffset.begin();

    // while(max > -1 || itr != tempoffset.end()) {

    // while((itr->second.second == false) && itr != tempoffset.end()) {

    // itr++;
    // }
    // if ((itr->second.first).size() >= max || next_biggest == tempoffset.end()) {
    // cout << "oh" << endl;
    // next_biggest = itr;
    // max = (itr->second.first).size();
    // cout << (itr->second.first).size() << endl;
    // itr++;
    // continue;
    // }


    // if (itr == tempoffset.end() || itr == next_biggest ) {
    // cout << "b" << endl;
    // bool notfound = true;
    // while(notfound) {

    // for (int offsetx = 0; offsetx < offset.Width() + 1 && offsetx < 16 && notfound; offsetx++) {
    // for (int offsety = 0; offsety < offset.Height() + 1 && offsety < 16; offsety++) {

    // if(validHashInsertion(offsetx,offsety,next_biggest,hash_data,input)) {

    // Offset v;
    // v.dx = offsetx;
    // v.dy = offsety;
    // cout << offsetx << endl;
    // cout << offsety << endl;
    // cout << endl;
    // offset.SetPixel(next_biggest->first.first,next_biggest->first.second,v);
    // notfound = false;
    // break;
    // }



    // }
    // }

    // if(notfound) {
    // cout << "o" << endl;
    // preset++;
    // allocateoffset(max,preset,offset);
    // itr = tempoffset.begin();
    // while(itr != tempoffset.end()) {
    // itr->second.second = true;
    // itr++;
    // }
    // itr = tempoffset.begin();
    // break;
    // }


    // }
    // if (!notfound) {
    // itr->second.second = false;
    // itr = tempoffset.begin();
    // max = 0;
    // next_biggest = tempoffset.end();
    // break;
    // }
    // else {
    // cerr << "whaaaaaaaaaaat?" << endl;
    // }

    // }

    // itr++;
    // cout << "a" << endl;

    // }






}


void UnCompress(const Image<bool> &occupancy, const Image<Color> &hash_data, const Image<Offset> &offset,
                Image<Color> &output) {
    output.Allocate(occupancy.Width(),occupancy.Height());
    Color white;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    for (int i = 0; i < occupancy.Width(); i++) {
        for (int j = 0; j < occupancy.Height(); j++) {
            if (!occupancy.GetPixel(i,j)) {
                output.SetPixel(i,j,white);
            }
            else {
                Color tempcolor;
                // tempcolor.r = 0;
                // tempcolor.g = 0;
                // tempcolor.b = 0;
                Offset temp =  offset.GetPixel(i % offset.Width(), j % offset.Height());
                unsigned char dx = temp.dx;
                unsigned char dy = temp.dy;
                tempcolor =  hash_data.GetPixel((i + dx) % hash_data.Width(), (j + dy) % hash_data.Height());


                output.SetPixel(i,j,tempcolor);
            }

        }
    }

}


// ===================================================================================================
// ===================================================================================================

void Compare(const Image<Color> &input1, const Image<Color> &input2, Image<bool> &output) {

    // confirm that the files are the same size
    if (input1.Width() != input2.Width() ||
            input1.Height() != input2.Height()) {
        std::cerr << "Error: can't compare images of different dimensions: "
                  << input1.Width() << "x" << input1.Height() << " vs "
                  << input2.Width() << "x" << input2.Height() << std::endl;
    } else {

        // confirm that the files are the same size
        output.Allocate(input1.Width(),input1.Height());
        int count = 0;
        for (int i = 0; i < input1.Width(); i++) {
            for (int j = 0; j < input1.Height(); j++) {
                Color c1 = input1.GetPixel(i,j);
                Color c2 = input2.GetPixel(i,j);
                if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b)
                    output.SetPixel(i,j,true);
                else {
                    count++;
                    output.SetPixel(i,j,false);
                }
            }
        }

        // confirm that the files are the same size
        if (count == 0) {
            std::cout << "The images are identical." << std::endl;
        } else {
            std::cout << "The images differ at " << count << " pixel(s)." << std::endl;
        }
    }
}

// ===================================================================================================
// ===================================================================================================


// to allow visualization of the custom offset image format
void ConvertOffsetToColor(const Image<Offset> &input, Image<Color> &output) {
    // prepare the output image to be the same size as the input image
    output.Allocate(input.Width(),input.Height());
    for (int i = 0; i < output.Width(); i++) {
        for (int j = 0; j < output.Height(); j++) {
            // grab the offset value for this pixel in the image
            Offset off = input.GetPixel(i,j);
            // set the pixel in the output image
            int dx = off.dx;
            int dy = off.dy;
            assert (dx >= 0 && dx <= 15);
            assert (dy >= 0 && dy <= 15);
            // to make a pretty image with purple, cyan, blue, & white pixels:
            int red = dx * 16;
            int green = dy *= 16;
            int blue = 255;
            assert (red >= 0 && red <= 255);
            assert (green >= 0 && green <= 255);
            output.SetPixel(i,j,Color(red,green,blue));
        }
    }
}


// ===================================================================================================
// ===================================================================================================

void usage(char* executable) {
    std::cerr << "Usage:  4 options" << std::endl;
    std::cerr << "  1)  " << executable << " compress input.ppm occupancy.pbm data.ppm offset.offset" << std::endl;
    std::cerr << "  2)  " << executable << " uncompress occupancy.pbm data.ppm offset.offset output.ppm" << std::endl;
    std::cerr << "  3)  " << executable << " compare input1.ppm input2.ppm output.pbm" << std::endl;
    std::cerr << "  4)  " << executable << " visualize_offset input.offset output.ppm" << std::endl;
}


// ===================================================================================================
// ===================================================================================================

int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage(argv[1]);
        exit(1);
    }

    if (argv[1] == std::string("compress")) {
        if (argc != 6) {
            usage(argv[1]);
            exit(1);
        }
        // the original image:
        Image<Color> input;
        // 3 files form the compressed representation:
        Image<bool> occupancy;
        Image<Color> hash_data;
        Image<Offset> offset;
        input.Load(argv[2]);
        Compress(input,occupancy,hash_data,offset);
        // save the compressed representation
        occupancy.Save(argv[3]);
        hash_data.Save(argv[4]);
        offset.Save(argv[5]);

    } else if (argv[1] == std::string("uncompress")) {
        if (argc != 6) {
            usage(argv[1]);
            exit(1);
        }
        // the compressed representation:
        Image<bool> occupancy;
        Image<Color> hash_data;
        Image<Offset> offset;
        occupancy.Load(argv[2]);
        hash_data.Load(argv[3]);
        offset.Load(argv[4]);
        // the reconstructed image
        Image<Color> output;
        UnCompress(occupancy,hash_data,offset,output);
        // save the reconstruction
        output.Save(argv[5]);

    } else if (argv[1] == std::string("compare")) {
        if (argc != 5) {
            usage(argv[1]);
            exit(1);
        }
        // the original images
        Image<Color> input1;
        Image<Color> input2;
        input1.Load(argv[2]);
        input2.Load(argv[3]);
        // the difference image
        Image<bool> output;
        Compare(input1,input2,output);
        // save the difference
        output.Save(argv[4]);

    } else if (argv[1] == std::string("visualize_offset")) {
        if (argc != 4) {
            usage(argv[1]);
            exit(1);
        }
        // the 8-bit offset image (custom format)
        Image<Offset> input;
        input.Load(argv[2]);
        // a 24-bit color version of the image
        Image<Color> output;
        ConvertOffsetToColor(input,output);
        output.Save(argv[3]);

    } else {
        usage(argv[0]);
        exit(1);
    }
}
