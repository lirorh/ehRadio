#!/usr/bin/env python3
"""Remove dayf_* keys from all display locale JSON files."""
import json, glob, os, sys, io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
os.chdir(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
dayf_keys = ['dayf_mon','dayf_tue','dayf_wed','dayf_thu','dayf_fri','dayf_sat','dayf_sun']
for f in sorted(glob.glob('src/locale/display/*.json')):
    d = json.load(open(f, 'r', encoding='utf-8'))
    removed = [k for k in dayf_keys if k in d]
    for k in removed:
        del d[k]
    if removed:
        json.dump(d, open(f, 'w', encoding='utf-8', newline='\n'), indent=2, ensure_ascii=False)
        open(f, 'a', encoding='utf-8').write('\n')
        print(f'stripped {len(removed)} dayf_ keys from {os.path.basename(f)}')
print('Done')
