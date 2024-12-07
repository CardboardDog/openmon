from PIL import Image
import os
import shutil
import toml

try:
    os.makedirs("build/src")
except:
    pass
try:
    os.makedirs("build/include")
except:
    pass
for src in os.listdir("source"):
    shutil.copy("source/"+src,"build/src/"+src)
for inc in os.listdir("include"):
    shutil.copy("include/"+inc,"build/include/"+inc)

mon_list = [None for i in os.listdir("mons/data")]
for mon in os.listdir("mons/data"):
    mon_data = toml.load("mons/data/"+mon)
    mon_list[mon_data["obj"]["id"]] = mon_data

mon_bin = "#include<mon_list.h>\nmon mon_list[] = {\n"
for mon in mon_list:
    data = "{\n"
    image = list(Image.open("mons/img/"+mon["obj"]["image"]).getdata())
    image = [(0 if pixel[0]==0 else 1) for pixel in image]
    image = str(image).replace("[","{").replace("]","}")+",\n"
    data+=image

    data+="om_"+mon["class"]["type"]+",\n"
    data+="\""+mon["class"]["name"]+"\",\n"
    data+=str(mon["data"]["health"])+",\n"
    data+=str(mon["obj"]["id"])+",\n"
    
    data += "{"
    data+=str(mon["data"]["attacks"][0][0])+","+str(mon["data"]["attacks"][0][1])+","+str(mon["data"]["attacks"][0][2])
    data += "},\n"

    data += "{"
    data+="\""+mon["data"]["attacks"][1][0]+"\",\""+mon["data"]["attacks"][1][1]+"\",\""+mon["data"]["attacks"][1][2]+"\""
    data += "},\n"

    data += "{"
    data+=str(mon["data"]["attacks"][2][0])+","+str(mon["data"]["attacks"][2][1])+","+str(mon["data"]["attacks"][2][2])
    data += "}\n"

    data+="\n},\n"
    mon_bin+=data

mon_bin+="};\n"

out_mon = open("build/src/mon_list.c","w")
out_mon.write(mon_bin);
out_mon.close()

mon_bin = "#ifndef __mon_list__\n#define __mon_list__\n#include<mon.h>\n"
mon_bin += f"#define mon_len {len(mon_list)}\n"
mon_bin += f"extern mon mon_list[{len(mon_list)}];\n"
mon_bin += "#endif\n"

out_mon = open("build/include/mon_list.h","w")
out_mon.write(mon_bin);
out_mon.close()

font = list(Image.open("game/tiny_font.png").getdata())
font = [(0 if pixel[0]==0 else 1) for pixel in font]
font = str(font).replace("[","{").replace("]","}")
font = "#include<font.h>\nunsigned char tiny_font[om_tiny_font_len] = "+font+";"

out_font = open("build/src/tiny_font.c","w")
out_font.write(font)
out_font.close()

tiles = list(Image.open("game/tiles.png").getdata())
tiles = [(0 if pixel[0]==0 else 1) for pixel in tiles]
tiles = str(tiles).replace("[","{").replace("]","}")
tiles = "#include<tiles.h>\nunsigned char tiles[om_tiles_len] = "+tiles+";"

out_tiles = open("build/src/tiles.c","w")
out_tiles.write(tiles)
out_tiles.close()

scenes = "#ifndef __scenes__\n#define __scenes__\n"
for scene in os.listdir("scenes"):
    scenes += "extern unsigned char "+scene.strip(".c")+"[112];\n"
scenes+="#endif\n"

out_scenes = open("build/include/scenes.h","w")
out_scenes.write(scenes)
out_scenes.close()

objects = ""
for file in os.listdir("build/src"):
    os.system(f"gcc -c build/src/{file} -o build/{file}.o -I build/include -lSDL2 -g")
    objects += f"build/{file}.o"+" "
os.system(f"gcc -o openmon {objects}-I build/include -lSDL2 -g")