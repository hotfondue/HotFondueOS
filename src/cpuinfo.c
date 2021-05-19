#include "../include/cpuinfo.h"

void print_binary(uint32 num)
{
  char bin_arr[32];
  uint32 index = 31;
  uint32 i;
  while (num > 0){
    if(num & 1){
      bin_arr[index] = '1';
    }else{
      bin_arr[index] = '0';
    }
    index--;
    num >>= 1;
  }

  for(i = 0; i < 32; ++i){
   if(i <= index)
      printch('0');
   else
     printch(bin_arr[i]);
  }
}

void cpuid(uint32 value, uint32 *eax, uint32 *ebx, unsigned int *ecx, uint32 *edx)
{
  uint32 eaxres, ebxres, ecxres, edxres;
  asm("xorl\t%eax, %eax");
  asm("xorl\t%ebx, %ebx");
  asm("xorl\t%ecx, %ecx");
  asm("xorl\t%edx, %edx");
  asm("movl\t%0, %%eax":"=m"(value));
  asm("cpuid");
  asm("movl\t%%eax, %0" : "=m" (eaxres));
  asm("movl\t%%ebx, %0" : "=m" (ebxres));
  asm("movl\t%%ecx, %0" : "=m" (ecxres));
  asm("movl\t%%edx, %0" : "=m" (edxres));
  *eax = eaxres;
  *ebx = ebxres;
  *ecx = ecxres;
  *edx = edxres;    
}

void print_eax(uint32 eax)
{
  uint32 step_id, model, family_id, proc_type, ext_mod_id, ext_fam_id;
  step_id = model = family_id = proc_type = ext_mod_id = ext_fam_id = eax;
  
  step_id &= (2 << 3) - 1;	//bits 0-3
  model >>= 4;	//bits 4-7
  model &= (2 << 3) - 1;
  family_id >>= 8;	//bits 8-11
  family_id &= (2 << 3) - 1;
  proc_type >>= 12;	//bits 12-13
  proc_type &= (2 << 1) - 1;
  ext_mod_id >>= 16;	//bits 16-19
  ext_mod_id &= (2 << 3) - 1;
  ext_fam_id >>= 20;	//bits 20-27
  ext_fam_id &= (2 << 7) - 1;

  print("\nEAX :-");
  print("\n\tStepping ID: ");
  printdec(step_id);
  print("\n\tModel: ");
  printdec(model);
  print("\n\tFamily ID: ");
  printdec(family_id);
  print("\n\tProcessor Type: ");
  printdec(proc_type);
  print("\n\tExtended Model ID: ");
  printdec(ext_mod_id);
  print("\n\tExtended Family ID: ");
  printdec(ext_fam_id);
}

void print_ebx(uint32 ebx)
{
  uint32 brand_index, cache_line_size, max_addr_id, init_apic_id;
  brand_index = cache_line_size = max_addr_id = init_apic_id = 0;
  char *bytes = (char*)&ebx;

  brand_index = bytes[0];	//bits 0-7
  cache_line_size = bytes[1];	//bits 8-15
  max_addr_id = bytes[2];	//bits 16-23
  init_apic_id = bytes[3];	//bits 24-31

  print("\nEBX :-");
  print("\n\tBrand Index: ");
  printdec(brand_index);
  print("\n\tCache Line Size: ");
  printdec(cache_line_size);
  print("\n\tMax Addressable ID for Logical Processors: ");
  printdec(max_addr_id);
  print("\n\tInitial APIC ID: ");
  printdec(init_apic_id);
}

void print_edx(uint32 edx)
{
  print("\nEDX :-");
  print("\n\tbit-31 [ ");
  print_binary(edx);
  print(" ] bit-0");
  print("\n\tBit 0 : FPU-x87 FPU on Chip");
  print("\n\tBit 1 : VME-Virtual-8086 Mode Enhancement");
  print("\n\tBit 2 : DE-Debugging Extensions");
  print("\n\tBit 3 : PSE-Page Size Extensions");
  print("\n\tBit 4 : TSC-Time Stamp Counter");
  print("\n\tBit 5 : MSR-RDMSR and WRMSR Support");
  print("\n\tBit 6 : PAE-Physical Address Extensions\n\n\n");
}

void cpuid_test()
{
  uint32 eax, ebx, ecx, edx;

  print("CPUID EAX = 01H");

  //see cpuid instruction in Intel Manual for more information
  cpuid(0x01, &eax, &ebx, &ecx, &edx);

  print_eax(eax);
  print_ebx(ebx);
  print_edx(edx);
}
