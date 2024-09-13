import os

# 指定源文件目录和目标 txt 文件路径
source_dir = "./"
target_file = "./code.txt"

# 获取源文件目录下的所有文件
files = os.listdir(source_dir)

# 打开目标 txt 文件
with open(target_file, "w") as target:
    # 遍历每个文件
    for file in files:
        # 检查文件扩展名是否为 .cpp 或 .h
        if file.endswith(".cpp") or file.endswith(".h"):
            file_path = os.path.join(source_dir, file)
            
            # 打开源文件并读取内容
            with open(file_path, "r", encoding="utf-8") as source:
                content = source.read()
            
            # 将源文件内容写入目标 txt 文件
            target.write(f"// File: {file}\n")
            target.write(content)
            target.write("\n\n")

print("文件合并完成！")