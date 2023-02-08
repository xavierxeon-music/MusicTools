#ifndef FileHPP
#define FileHPP

#include <Tools/File.h>

bool File::exists(const std::string& fileName)
{
   FILE* file = fopen(fileName.c_str(), "r");
   if (!file)
      return false;

   fclose(file);
   return true;
}

Bytes File::load(const std::string& fileName)
{
   FILE* file = fopen(fileName.c_str(), "r");
   if (!file)
      return Bytes();

   fseek(file, 0, SEEK_END);
   size_t fileSize = ftell(file);
   fseek(file, 0, SEEK_SET);

   Bytes bytes(fileSize);
   const size_t br = fread(bytes.data(), 1, fileSize, file);
   (void)br;

   fclose(file);
   return bytes;
}

void File::save(const Bytes& bytes, const std::string& fileName)
{
   if (bytes.empty())
      return;

   FILE* file = fopen(fileName.c_str(), "w");
   if (file)
      return;

   fwrite(bytes.data(), 1, bytes.size(), file);

   fclose(file);
}

#endif // NOT FileHPP
