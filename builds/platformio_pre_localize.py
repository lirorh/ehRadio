Import("env")
import shutil
import os
import sys

# Skip during clean/erase/filesystem operations
skip_operations = ["clean", "fullclean", "erase", "buildfs", "uploadfs"]
if any(op in " ".join(sys.argv) for op in skip_operations):
    Return()

project_dir = env.get("PROJECT_DIR", os.getcwd())
env_name = env["PIOENV"]

# Font source directory (converted GFXfont .h files)
src_dir = os.path.join(project_dir, "src", "displays", "fonts")

# Destination in the Adafruit GFX Library (one per env)
dst_dir = os.path.join(project_dir, ".pio", "libdeps", env_name,
                       "Adafruit GFX Library", "Fonts")

if not os.path.exists(dst_dir):
    print(f"  [font] Destination not found: {dst_dir}")
    print(f"  [font] Skipping font copy for {env_name}")
    Return()

# Copy all .h files from fonts directory to the library Fonts folder
count = 0
for fn in sorted(os.listdir(src_dir)):
    if fn.endswith(".h"):
        src = os.path.join(src_dir, fn)
        dst = os.path.join(dst_dir, fn)
        shutil.copyfile(src, dst)
        print(f"  [font] {fn} -> Fonts/{fn}")
        count += 1

if count == 0:
    print(f"  [font] No .h files found in {src_dir}")
else:
    print(f"  [font] {count} font(s) installed for {env_name}")
