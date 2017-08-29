import os
import sys
import configparser
import logging

log = logging
log.basicConfig(level=logging.DEBUG)

BASE_SECTION = "base-section"
ROOT_DIR = "root_dir"
LINK_SECTION = "link-section"

if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(1)
    is_unlink = False
    if len(sys.argv) > 2 and sys.argv[2].lower() == "unlink":
        is_unlink = True
    ini_file_path = os.path.abspath(sys.argv[1])
    if not os.path.isfile(ini_file_path):
        sys.exit(2)
    root_dir_path = None
    link_maps = {}
    with open(ini_file_path, "r") as f:
        ini_cfg = configparser.ConfigParser()
        ini_cfg.optionxform = str
        ini_cfg.read_file(f)
        root_dir_path = os.path.abspath(ini_cfg[BASE_SECTION][ROOT_DIR])
        for key in ini_cfg[LINK_SECTION]:
            link_maps[key] = ini_cfg[LINK_SECTION][key]
    if not root_dir_path or not os.path.isdir(root_dir_path):
        sys.exit(3)
    exist_links = []
    for root, dirs, files in os.walk(root_dir_path):
        for dir in dirs:
            abs_dir_path = os.path.join(root, dir)
            if os.path.islink(abs_dir_path):
                exist_links.append(abs_dir_path)
        for file in files:
            abs_file_path = os.path.join(root, file)
            if os.path.islink(abs_file_path):
                exist_links.append(abs_file_path)
    for exist_link in exist_links:
        os.remove(exist_link)
    if is_unlink:
        sys.exit(0)
    all_ok = True
    for key, val in link_maps.items():
        try:
            real_path = os.path.join(root_dir_path, val)
            link_path = os.path.join(root_dir_path, key)
            if (not os.path.exists(os.path.dirname(link_path))):
                os.makedirs(os.path.dirname(link_path))
            os.symlink(real_path, link_path)
        except FileExistsError as e:
            log.error(e)
        except FileNotFoundError as e:
            log.error(e)
            all_ok = False
    log.debug(all_ok and "All Ok" or "Some Fail")
    sys.exit(all_ok and 0 or -1)


