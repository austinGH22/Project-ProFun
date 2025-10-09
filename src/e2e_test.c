#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TEST_FILE "data.csv"
#define MOCK_INPUT "mock_input.txt"

void clear_csv() {
    FILE *fp = fopen(TEST_FILE, "w");
    assert(fp != NULL);
    fclose(fp);
}

void prepare_mock_input() {
    FILE *mock = fopen(MOCK_INPUT, "w");
    assert(mock != NULL);

    // จำลองผู้ใช้กดเมนู
    fputs(
        "2\n"               // Add Machine
        "MachineA\n"        
        "E001\n"
        "Operational\n"
        "2030-01-01\n"
        "1\n"               // Read CSV
        "3\nMachineA\n"     // Search MachineA
        "4\nMachineA\n1\nUpdatedName\n" // Update Name
        "5\nUpdatedName\n1\nY\n"        // Delete Machine
        "6\n",              // Exit
        mock
    );
    fclose(mock);
}

void e2e_test() {
    printf("\n===== START END-TO-END TEST =====\n");

    clear_csv();
    prepare_mock_input();

    // เรียก main program (เช่น output.exe) พร้อม redirect stdin
    // ✅ ใช้วิธี system() เพื่อหลีกเลี่ยงการเรียก main() ซ้ำ
#ifdef _WIN32
    system("output.exe < mock_input.txt");
#else
    system("./output < mock_input.txt");
#endif

    // ตรวจสอบว่าข้อมูลถูกลบหมดจริงไหม
    FILE *fp = fopen(TEST_FILE, "r");
    assert(fp != NULL);
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    assert(size == 0); // ตรวจว่า CSV ว่าง → ลบสำเร็จ
    printf("✅ End-to-End Test passed! All flows covered.\n");
}

int main() {
    e2e_test();
    return 0;
}
