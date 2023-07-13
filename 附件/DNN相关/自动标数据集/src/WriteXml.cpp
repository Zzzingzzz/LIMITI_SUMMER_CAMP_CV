#include "WriteXml.hpp"

/**
 * @brief 生成xml文件
 * @param image_path 图片的路径
 * @param infos 图片中识别出的物体信息
 */
void WriteXml::Write(std::string image_path, cv::Mat frame, std::vector<DNN::DNN_infos> infos)
{
    std::vector<std::string> xmlpaths = WriteXml::xml_paths(image_path);

    freopen(xmlpaths[0].c_str(),"w",stdout);

    printf("<annotation>\n");

    std::cout << "       <folder>" << xmlpaths[1] << "</folder>" << std::endl;

    std::cout << "       <filename>" << xmlpaths[2] << "</filename>" << std::endl;

    std::cout << "       <path>" << image_path << "</path>" << std::endl;

    printf("       <source>\n              <database>Unknown</database>\n       </source>\n");

    printf("       <size>\n              <width>%d</width>\n              <height>%d</height>\n              <depth>3</depth>\n       </size>\n",frame.cols,frame.rows);

    printf("       <segmented>0</segmented>\n");

    for(size_t i=0; i<infos.size(); i++)
    {
        printf("       <object>\n");

        std::cout << "              <name>" << infos[i].label << "</name>" << std::endl;

        printf("              <pose>Unspecified</pose>\n              <truncated>0</truncated>\n              <difficult>0</difficult>\n");

        int left=infos[i].roi.tl().x, right=infos[i].roi.br().x;
        int top=infos[i].roi.tl().y, bottom=infos[i].roi.br().y;

        printf("              <bndbox>\n");

        printf("                     <xmin>%d</xmin>\n",left);
        printf("                     <ymin>%d</ymin>\n",top);
        printf("                     <xmax>%d</xmax>\n",right);
        printf("                     <ymax>%d</ymax>\n",bottom);

        printf("              </bndbox>\n");

        printf("       </object>\n");
    }

    printf("</annotation>");

    fclose(stdout);
}

/**
 * @brief 获取生成的xml的文件的路径
 * @param xmlfolder_path 保存xml文件夹的路径
 * @param image_path 图片的路径
 * @return std::vector<std::string> 生成的xml的文件的路径
 */
std::vector<std::string> WriteXml::xml_paths(std::string image_path)
{
    char xml_file[300]={0};

    int flag=-1;
    for(int i=image_path.size(); i>=0; i--)
        if(image_path[i]=='/')
        {
            flag=i;
            break;
        }

    for(int i=0; i<flag; i++)
        xml_file[i]=image_path[i];
        
    xml_file[flag]='/';
    xml_file[flag+1]='x';
    xml_file[flag+2]='m';
    xml_file[flag+3]='l';

    int end;
    for(int i=flag; image_path[i]!='.'; i++, end=i+4)
        xml_file[i+4]=image_path[i];

    xml_file[end]='.';
    xml_file[end+1]='x';
    xml_file[end+2]='m';
    xml_file[end+3]='l';

    std::string xmlname = xml_file;

    char file[100]={0};

    int flag2;
    for(int i=flag-1; image_path[i]!='/'; i--)
        flag2=i;

    for(int i=flag2,k=0; i<flag; i++,k++)
        file[k]=image_path[i];

    std::string filename=file;

    char jpgname[100]={0};

    for(int i=flag+1,k=0; i<image_path.size(); i++,k++)
        jpgname[k]=image_path[i];

    std::string jpg_name=jpgname;

    std::vector<std::string> ans;

    ans.push_back(xmlname);
    ans.push_back(filename);
    ans.push_back(jpg_name);

    return ans;
}