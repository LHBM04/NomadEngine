import os
import re
import sys

def expected_guard_macro(file_path):
    """파일 경로에 맞춰 include guard 매크로 이름 생성"""
    file_name = os.path.basename(file_path)
    name = os.path.splitext(file_name)[0]
    return f"GUARD_{name.upper()}_H"

def check_guard(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    guard_ifndef = None
    guard_define = None

    for i in range(min(10, len(lines))):
        ifndef_match = re.match(r'#ifndef\s+([A-Z0-9_]+)', lines[i])
        define_match = re.match(r'#define\s+([A-Z0-9_]+)', lines[i])

        if ifndef_match:
            guard_ifndef = ifndef_match.group(1)
        if define_match:
            guard_define = define_match.group(1)

        if guard_ifndef and guard_define:
            break

    expected = expected_guard_macro(file_path)

    if guard_ifndef != expected or guard_define != expected:
        print(f"[ERROR] {file_path}")
        print(f"  - Found:   #ifndef {guard_ifndef}, #define {guard_define}")
        print(f"  - Expect:  #ifndef {expected}, #define {expected}")
        return False

    return True

def scan_directory(path):
    failed = 0
    for root, _, files in os.walk(path):
        for file in files:
            if file.endswith('.h'):
                full_path = os.path.join(root, file)
                if not check_guard(full_path):
                    failed += 1
    return failed

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("사용법: python check_include_guards.py <경로>")
        sys.exit(1)

    target_dir = sys.argv[1]

    error_count = scan_directory(target_dir)
    if error_count == 0:
        print("✅ 모든 include guard가 올바릅니다.")
    else:
        print(f"❌ 총 {error_count}개 파일에서 오류가 발견되었습니다.")
        sys.exit(2)
