#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

std::string ToHex(const std::string& s, bool upper_case){
  std::ostringstream ret;
  for (std::string::size_type i = 0; i < s.length(); ++i) {
    int z = s[i]&0xff;
    ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::nouppercase : std::nouppercase) << z;
  }
  return ret.str();
}

struct MIME {

  std::vector<std::string> header { "2321","a1b2c3d4","d4c3b2a1","0a0d0d0a","edabeedb","53514c69746520666f726d6174203300",
"53503031","00","000000000000000000000000000000000000000000","bebafeca","00014244","00014454","54444624",
"54444546","00010000","00000100","667479703367","1f9d","1fa0","4241434b4d494b454449534B","425a68","474946383761","474946383961",
"49492a00","4d4d002a","49492a00100000004352","802a5fd7","524e4301","524e4302","53445058","58504453",
"762f3101","425047fb","ffd8ffdb","ffd8ffe000104a4649460001","ffd8ffee","ffd8ffe1","464f524d","464f524d","464f524d","464f524d","464f524d","464f524d","464f524d",
"464f524d","464f524d","464f524d","464f524d","464f524d","494e4458","4c5a4950","4d5a","504b0304","504b0506","504b0708",
"526172211a0700","526172211a070100","5a4d","7f454c46","89504e470d0a1a0a","c9","cafebabe","efbbbf","feedface","feedfacf","feedfeed","cefaedfe","cffaedfe","fffe",
"fffe0000","25215053","255044462d","3026b2758e66cf11a6d900aa0062ce6c",
"2453444930303031","4f676753","38425053","52494646","52494646","fffb","494433","424d","4344303031","53494d504c452020",
"3d202020202020202020202020202020202020202054",
"664c6143","4d546864","d0cf11e0a1b11ae1","6465780a30333500","4b444d","43723234","41474433",
"05070000424f424f05070000000000000000000001","0607e100424f424f0607e10000000000000000000001","455202000000",
"8b455202000000","7801730d626260","78617221",
"504d4f43434d4f43","4e45531a","7573746172003030","7573746172202000","746f7833","4d4c5649","44434d0150413330",
"377abcaf271c","1f8b","fd377a585a0000","04224d18",
"4d534346","535a444488f02733","464c4946","1a45dfa3",
"4d494c20","41542654464f524d","3082","4449434d",
"774f4646","774f4632","3c3f786d6c20","0061736d",
"cf8401","435753","465753","213c617263683e",
"52494646","27051956","7b5c72746631","54415045","47",
"000001ba","000001ba","47","000001b3","7801","789c",
"78da","62767832","4f5243","4f626a01","53455136",
"65877856","5555aaaa","785634","50415231",
"454d5832","454d5533","1b4c7561",
"626f6f6b000000006d61726b00000000","5b5a6f6e655472616e736665725d","5265636569766564","20020162a01eab0702000000",
"3748030200000000583530394b4559","85010c03","28b52ffd",
"3a290a","4a6f7921","310a3030","3c21444f43545950452068746d6c3e","3c68746d6c3e","23696e636c756465","7061636b61676520",
"0001028bae6c5b291cc78e25470b8625","56455253494f4e20352e30300d0a426567696e2056422e46","466f726d31203d2034362c2034372c20","547970653d4578650d0a466f726d3d","696d706f727420","3c3f706870" }; 


  std::vector<std::string> type { "shebang","pcap","pcap","pcapng","rpm","sqlitedb/sqlite/db","bin","PIC/PIF/SEA/YTR","PDB","DBA","DBA","TDA","TDF$",
"TDEF","n/a","ico","3gp/3g2","z/tar.z","z/tar.z","bac","bz2","gif","gif","tif/tiff","tif/tiff","cr2","cin","n/a","n/a","dpx","dpx","exr",
"bpg","jpg/jpeg","jpg/jpeg","jpg/jpeg","jpg/jpeg","ilbm/lbm/ibm/iff","8svx/8sv/svx/snd/iff","acbm/iff","anbm/iff","anim/iff","faxx/fax/iff",
"ftxt/iff","smus/smu/mus/iff","cmus/mus/iff","yuvn/yuv/iff","iff","aiff/aif/aifc/snd/iff","idx","lz","exe/dll",
"zip/aar/apk/docx/epub/ipa/jar/kmz/maff/odp/ods/odt/pk3/pk4/pptx/usdz/vsdx/xlsc/xpi",
"zip/aar/apk/docx/epub/ipa/jar/kmz/maff/odp/ods/odt/pk3/pk4/pptx/usdz/vsdx/xlsc/xpi",
"zip/aar/apk/docx/epub/ipa/jar/kmz/maff/odp/ods/odt/pk3/pk4/pptx/usdz/vsdx/xlsc/xpi","rar","rar","exe","bin/axf/elf/o/prx/puff/ko/mod/so",
"png","com","class","n/a","n/a","n/a","n/a","n/a","n/a","n/a","n/a","ps","pdf","asf/wma/wmv","n/a","ogg/oga/ogv","psd","wav","avi","mp3","mp3",
"bpm/dib","iso","fits","fits","flac","mid/midi","doc/xls/ppt/msg","dex","vmdk","crx","fh8","cwk","cwk","toast","toast","dmg","xar","dat","nes",
"tar","tar","tox","MLV","n/a","7z","gz/tar.gz","xz/tar.xz","lz4","cab","??_","flif","mkv/mka/mks/mk3d/webm","stg","djvu/djv","der","dcm","woff",
"woff2","XML","wasm","lep","swf","swf","deb","webp","n/a","rtf","n/a","ts/tsv/tsa","m2p/vob","mpg/mpeg","mpg/mpeg","mpg/mpeg","zlib","zlib","zlib",
"lzfse","orc","avro","rc","p25/obt","pcv","pbt/pdt/pea/peb/pet/pgt/pict/pjt/pkt/pmt","n/a","ez2","ez3/iso","luac","alias","Identifier",
"eml","tde","kdb","pgp","zst","sml","n/a","srt","html","html","c/cpp","java","db.crypt1","frm","vbw","vbp","py","php"};




  std::string sniff(std::string path) {
    std::string result = "unknown";
    std::ifstream::pos_type size;
    char * memblock;

    std::ifstream file (path.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
    if (file.is_open()) {
      size = file.tellg();
      memblock = new char [size];
      file.seekg (0, std::ios::beg);
      file.read (memblock, size);
      file.close();
    
      std::string tohexed = ToHex(std::string(memblock, size), true);
      std::string fileMime;

      for (int i = 0; i < 32 && i < tohexed.size(); ++i) {
        fileMime += tohexed[i];
      }

      for (int i = 0; i < header.size(); ++i) {
        if (fileMime.substr(0, header[i].size()) == header[i]) {
          return type[i];
        }
      }
    }
    return result;
  }
};
