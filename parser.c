#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define path ".exe" // add path to exe file

/*
void ispis(struct SectionHeader){
	printf("Section header\n");
	printf("==============\n");
	printf("\t Name: \t \t\t\t %d%d\n", SectionHeader.name1,SectionHeader.name2);
	printf("\t VirtualSize: \t \t\t 0x%08x\n", SectionHeader.virtualSize);
	printf("\t VirtualAddress: \t \t 0x%08x\n", SectionHeader.virtualAddress);
	printf("\t SizeOfRawData: \t \t 0x%08x\n", SectionHeader.sizeOfRawData);
	printf("\t PointerToRawData: \t \t 0x%08x\n", SectionHeader.pointerToRawData);
	printf("\t PointerToRealocations:  \t 0x%08x\n", SectionHeader.pointerToRealocations);
	printf("\t PointerToLineNum: \t \t 0x%08x\n", SectionHeader.pointerToLineNum);
	printf("\t NumOfRealocations: \t \t 0x%04x\n", SectionHeader.numOfRealocations);
	printf("\t NumOfLineNumbers: \t \t 0x%04x\n", SectionHeader.numOfLineNumbers);
	printf("\t Characteristics: \t \t 0x%08x\n", SectionHeader.characteristics);
	printf("\n");
	printf("\n");
}
*/
struct MZHEADER{
	short signature; 
	short lastPageSize;
	short TotalPagesInFile;
	short relocationItems;
	short paragraphsInHeader;
	short minExtraPar;
	short maxExtraPar;
	short initialStackSegment;
	short initialStackPointer;
	short complementedCheckSum;
	short initialInstructionPointer;
	short initialCodeSegment;
	short relocationTableOffset;
	short overlayNumber;
	int reserved1;
	int reserved2;
	int reserved3;
	int reserved4;
	int reserved5;
	int reserved6;
	int reserved7;
	int reserved8;
    int OffsetToNewHeader;	
    
}MZHeader;


struct PEHEADER{
	int PESignature;
	short machine;
	short numOfSections;
	int timeDateStamp;
	int symbolPointer;
	int numOfSymbol;
	short sizeOfOptionalHeader;
	short characteristics;
	
    
}PEHeader;


struct OPTIONALHEADER{
	short magic;
	short linkerVersion;
	int sizeOfCode;
	int sizeOfIData;
	int sizeOfUData;
	int adressOfEntryPoint;
	int baseOfCode;
	int baseOfData;
	int imageBase;
	int sectionAlignment;
	int fileAlignment;
	int systemVersion;
	int imageVersion;
	int subsystemVersion;
	long int reserved1;
	long int sizeOfImage;
	long int sizeOfHeaders;
	long int Checksum;
	short subsystem;
	short DLLChar;
	long int sizeOfStackReserve;
	long int sizeOfStackCommit;
	long int sizeOfHeapReserve;
	long int sizeOfHeapCommit;
	long int LoaderFlags;
	long int sizeOfDataDirectory;
	int importDirVirtualAdress;
	int importDirSize;
}OptionalHeader;

struct VA{
	int virtualAdress;
	int resourceDirSize;
}va;

struct SECTIONHEADER{
	int name1;
	int name2;
	int virtualSize;
	int virtualAddress;
	int sizeOfRawData;
	int pointerToRawData;
	int pointerToRealocations;
	int pointerToLineNum;
	short numOfRealocations;
	short numOfLineNumbers;
	long int characteristics;
	
	
}SectionHeader;


struct EXPORTTABLE{
	int Characteristics;
	int TimeDateStamp;
	char MajorVersion;
	char MinorVersion;	/*8bitova*/
	int NameRVA;
	int OrdinalBase;
	int NumberOfFuncions;
	int NumberOfNames;
	int AdressTableRVA;
	int NamePointerTableRVA;
	int OrdinalTableRVA;
	

}ExportTable;

struct IMPORTTABLE{
	int originalFirstThunk;
	int timeDateStamp;
	int forwarderCham;
	int name;
	int firstThunk;
	
}ImportTable;


struct IMPROTTHUNK{
	int data;
	
}ImportThunk;


struct ORDINAL{
	short data;
	
}Ordinal;



int main(void){
	
	/*
	char ime1[32];
	char ime2[32];
	
	*/
	
	/*procitati iz datoteke i zapisati u strukturu*/
	
	int i;
	
	int Ipointeric=0, Epointeric=0, Iadresica, Eadresica;
	int import;
	/*int Isize;*/
	int offset;
	FILE *f=NULL;
	f=fopen(path, "rb");
	if(f==NULL){
		printf("Error\n");
		exit(1);
	}

	if(fread(&MZHeader, sizeof(MZHeader),1,f)!=1){
		printf("failed to read header\n");
		exit(1);
	}
		
	printf("MZ header\n");
	printf("=========\n");
	printf("\t Magic: \t\t\t 0x%04x\n ", MZHeader.signature);
	printf("\t BytesOnLastPageOfFile: \t 0x%04x\n", MZHeader.lastPageSize);
	printf("\t TotalPagesInFile: \t\t 0x%04x\n", MZHeader.TotalPagesInFile);
	printf("\t RelocationItems: \t\t 0x%04x\n", MZHeader.relocationItems);
	printf("\t ParagraphsInHeader: \t\t 0x%04x\n", MZHeader.paragraphsInHeader);
	printf("\t MinExtraPar: \t\t\t 0x%04x\n", MZHeader.minExtraPar);
	printf("\t MaxExtraPar: \t\t\t 0x%04x\n", MZHeader.maxExtraPar);
	printf("\t InitialStackSegment: \t\t 0x%04x\n", MZHeader.initialStackSegment);
	printf("\t InitialStackPointer: \t\t 0x%04x\n", MZHeader.initialStackPointer);
	printf("\t ComplementedCheckSum: \t\t 0x%04x\n", MZHeader.complementedCheckSum);
	printf("\t InitialInstructionPointer: \t 0x%04x\n", MZHeader.initialInstructionPointer);
	printf("\t InitialCodeSegment: \t\t 0x%04x\n", MZHeader.initialCodeSegment);
	printf("\t RelocationTableOffset: \t 0x%04x\n", MZHeader.relocationTableOffset);
	printf("\t OverlayNumber: \t\t 0x%04x\n", MZHeader.overlayNumber);
	printf("\t Reserved: \t\t\t 0x%016x%x\n", MZHeader.reserved1, MZHeader.reserved2);
	printf("\t \t \t\t\t 0x%016x%x\n", MZHeader.reserved3, MZHeader.reserved4);
	printf("\t \t \t\t\t 0x%016x%x\n", MZHeader.reserved5, MZHeader.reserved6);
	printf("\t \t \t\t\t 0x%016x%x\n", MZHeader.reserved7, MZHeader.reserved8);
    printf("\t OffsetToNewHeader: \t\t 0x%08x\n", MZHeader.OffsetToNewHeader);
	printf("\n");
	printf("\n");

    offset=MZHeader.OffsetToNewHeader-MZHeader.relocationTableOffset;

    fseek(f, offset,SEEK_CUR);
	if(fread(&PEHeader, sizeof(PEHeader),1,f)!=1){
		printf("failed to read header\n");
		exit(1);
	}
 	printf("PE header\n");
	printf("=========\n");
	printf("\t Signature: \t\t\t 0x%08x\n", PEHeader.PESignature);
	printf("\t Machine: \t\t\t 0x%04x\n", PEHeader.machine);
	printf("\t NumOfSections: \t\t 0x%04x\n", PEHeader.numOfSections);
	printf("\t TimeDateStamp: \t\t 0x%08x\n", PEHeader.timeDateStamp);
	printf("\t SymbolPointer: \t\t 0x%08x\n", PEHeader.symbolPointer);
	printf("\t NumberOfSymbol: \t\t 0x%08x\n", PEHeader.numOfSymbol);
	printf("\t SizeOfOptionalHeader: \t\t 0x%04x\n", PEHeader.sizeOfOptionalHeader);
	printf("\n");
	printf("\n");




	if(fread(&OptionalHeader, sizeof(OptionalHeader),1,f)!=1){
		printf("failed to read header\n");
		exit(1);
	}
	
	printf("Optional header\n");
	printf("===============\n");
	printf("\t Magic: \t\t\t 0x%04x\n", OptionalHeader.magic);
	printf("\t LinkerVersion: \t\t 0x%04x\n", OptionalHeader.linkerVersion);
	printf("\t SizeOfCode: \t\t\t 0x%08x\n", OptionalHeader.sizeOfCode);
	printf("\t SizeOfInitializedData: \t 0x%08x\n", OptionalHeader.sizeOfIData);
	printf("\t SizeOfUninitializedData: \t 0x%08x\n", OptionalHeader.sizeOfUData);
	printf("\t AdressOfEntryPoint: \t\t 0x%08x\n", OptionalHeader.adressOfEntryPoint);
	printf("\t baseOfCode: \t\t\t 0x%08x\n", OptionalHeader.baseOfCode);
	printf("\t baseOfData: \t\t\t 0x%08x\n", OptionalHeader.baseOfData);
	printf("\t imageBase: \t\t\t 0x%08x\n", OptionalHeader.imageBase);
	printf("\t sectionAlignment: \t\t 0x%08x\n", OptionalHeader.sectionAlignment);
	printf("\t fileAlignment: \t\t 0x%08x\n", OptionalHeader.fileAlignment);
	printf("\t SystemVersion: \t\t %d\n", OptionalHeader.systemVersion);
	printf("\t imageVersion: \t\t\t %d\n", OptionalHeader.imageVersion);
	printf("\t subsystemVersion: \t\t %d\n", OptionalHeader.subsystemVersion);
	printf("\t Reserved: \t\t\t 0x%08x\n", OptionalHeader.reserved1);
	printf("\t sizeOfImage: \t\t\t 0x%08x\n", OptionalHeader.sizeOfImage);
	printf("\t sizeOfHeaders: \t\t 0x%08x\n", OptionalHeader.sizeOfHeaders);
	printf("\t Checksum: \t\t\t 0x%08x\n", OptionalHeader.Checksum);
	printf("\t subsystem: \t\t\t 0x%04x\n", OptionalHeader.subsystem);
	printf("\t DLLChar: \t\t\t 0x%04x\n", OptionalHeader.DLLChar);
	printf("\t sizeOfStackReserve: \t\t 0x%08x\n", OptionalHeader.sizeOfStackReserve);
	printf("\t sizeOfStackCommit: \t\t 0x%08x\n", OptionalHeader.sizeOfStackCommit);
	printf("\t sizeOfHeapReserve: \t\t 0x%08x\n", OptionalHeader.sizeOfHeapReserve);
	printf("\t sizeOfHeapCommit: \t\t 0x%08x\n", OptionalHeader.sizeOfHeapCommit);
	printf("\t LoaderFlags: \t\t\t 0x%08x\n", OptionalHeader.LoaderFlags);
	printf("\t NumberOfDataDirectory: \t 0x%08x\n", OptionalHeader.sizeOfDataDirectory);
	printf("\t Export Table: \t\t\t 0x%08x\n", OptionalHeader.importDirVirtualAdress);
	printf("\t Export table size: \t\t 0x%08x\n", OptionalHeader.importDirSize);
	printf("\t Resource Directory:\n");
	printf("\n");
	for(i=0;i<OptionalHeader.sizeOfDataDirectory-1;i++){
	if(fread(&va, sizeof(va),1,f)!=1){
		printf("failed to read header\n");
		exit(1);
	}
	switch(i){
		
		case 0:{
			import=va.virtualAdress;
			/*Isize=va.resourceDirSize;*/
			printf("\t IMPORT table: \t\t\t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t\t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 1:{
			printf("\t RESOURCE table:  \t\t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 2:{
			printf("\t EXCEPTION table: \t\t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 3:{
			printf("\t CERTIFICATE table: \t\t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 4:{
			printf("\t BASE RELOCATION table: \t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 5:{
			printf("\t DEBUG directory: \t\t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 6:{
			printf("\t Architecture specific data: \t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 7:{
			printf("\t GLOBAL pointer register: \t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 8:{
			printf("\t TLS table: \t\t\t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 9:{
			printf("\t LOAD CONFIGURATION table: \t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 10:{
			printf("\t BOUND IMPORT table: \t\t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 11:{
			printf("\t IMPORT address table: \t\t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 12:{
			printf("\t DELAY IMPORT descriptor: \t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 13:{
			printf("\t CLI header: \t\t\t 0x%08x\n", va.virtualAdress);
			printf("\t Size: \t\t\t \t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
		case 14:{
			printf("\t\t\t \t\t 0x%08x\n", va.virtualAdress);
			printf("\t \t\t \t\t 0x%08x\n", va.resourceDirSize);
			printf("-------------------------------------------------------\n");
			break;
		}
	
	
	}
	}printf("\n");
	
	
	
	
	
	for(i=0;i<PEHeader.numOfSections;i++){
		
	if(fread(&SectionHeader, sizeof(SectionHeader),1,f)!=1){
	printf("failed to read header\n");
	exit(1);
	}
		if(SectionHeader.name1 == 0x6164692E/* || SectionHeader.name1 == 0x6164722E*/){
			Ipointeric=SectionHeader.pointerToRawData;
			Iadresica=SectionHeader.virtualAddress;
		}
		else if(SectionHeader.name1==0x6164652E){
			Epointeric=SectionHeader.pointerToRawData;
			Eadresica=SectionHeader.virtualAddress;
		}
		
	printf("Section header\n");
	printf("==============\n");
	printf("\t Name: \t \t\t\t 0x%x%x\n", SectionHeader.name1,SectionHeader.name2);
	printf("\t VirtualSize: \t \t\t 0x%08x\n", SectionHeader.virtualSize);
	printf("\t VirtualAddress: \t \t 0x%08x\n", SectionHeader.virtualAddress);
	printf("\t SizeOfRawData: \t \t 0x%08x\n", SectionHeader.sizeOfRawData);
	printf("\t PointerToRawData: \t \t 0x%08x\n", SectionHeader.pointerToRawData);
	printf("\t PointerToRealocations:  \t 0x%08x\n", SectionHeader.pointerToRealocations);
	printf("\t PointerToLineNum: \t \t 0x%08x\n", SectionHeader.pointerToLineNum);
	printf("\t NumOfRealocations: \t \t 0x%04x\n", SectionHeader.numOfRealocations);
	printf("\t NumOfLineNumbers: \t \t 0x%04x\n", SectionHeader.numOfLineNumbers);
	printf("\t Characteristics: \t \t 0x%08x\n", SectionHeader.characteristics);
	printf("\n");
	printf("\n");
	
	
	}
	

	if(Ipointeric!=0){
		offset=import+Ipointeric-Iadresica;
	fseek(f, offset, SEEK_SET );
	printf("Import Table\n");
	printf("============\n");
	i=0;
	
	while(1){
		
	if(fread(&ImportTable, sizeof(ImportTable),1,f)!=1){
		printf("failed to read header\n");
	exit(1);
	}
	
	
	printf("     Import Directory\n");
	printf("     ================\n");
	
	
	printf("\t Import Name Table RVA: \t 0x%08x\n", ImportTable.originalFirstThunk);
	printf("\t TimeDateStamp: \t\t 0x%08x\n", ImportTable.timeDateStamp);
	printf("\t Forwarder Chain: \t\t 0x%08x\n", ImportTable.forwarderCham);
	printf("\t NameRVA: \t\t\t 0x%08x\n", ImportTable.name);
	printf("\t Import Adress Table RVA: \t 0x%08x\n", ImportTable.firstThunk);
	
	
	/*
	printf("\t Import Name Table RVA: \t 0x%08x (phys: 0x%08x)\n", ImportTable.originalFirstThunk, ImportTable.originalFirstThunk-Iadresica);
	printf("\t TimeDateStamp: \t\t 0x%08x (phys: 0x%08x)\n", ImportTable.timeDateStamp,ImportTable.timeDateStamp-Ipointeric);
	printf("\t Forwarder Chain: \t\t 0x%08x (phys: 0x%08x)\n", ImportTable.forwarderCham,ImportTable.forwarderCham-Ipointeric);
	printf("\t NameRVA: \t\t\t 0x%08x (phys: 0x%08x)\n", ImportTable.name,ImportTable.name-Ipointeric);
	printf("\t Import Adress Table RVA: \t 0x%08x (phys: 0x%08x)\n", ImportTable.firstThunk,ImportTable.firstThunk-Ipointeric);
	*/
	
	
	if(ImportTable.originalFirstThunk==0) break;
	
	
	printf("\t Import Thunks\n");
	printf("\t =============\n");
	
	
	offset=ImportTable.originalFirstThunk-Iadresica+Ipointeric;
	
	while(1){
		/*printf("%x", Ipointeric);*/
	
	/*printf("%d", offset);*/
	fseek(f, offset, SEEK_SET);
	
	if(fread(&ImportThunk, sizeof(ImportThunk),1,f)!=1){
		printf("failed to read header\n");
		exit(1);
	}
	
	if(ImportThunk.data==0){
		break;
	
	}
	printf("\t    API: 0x%08x (phys: 0x%08x) --> Hint: 0x%08x \n", offset, offset-Ipointeric,ImportThunk.data );
	
	offset+=4;

	}
	i++;
	offset=import+Ipointeric-Iadresica+i*20;
	fseek(f, offset, SEEK_SET);
	
	}
	}
	
	
	
	printf("\n");
	printf("\n");
	
	
	
	
	
	
	
	if(Epointeric!=0){
		offset=OptionalHeader.importDirVirtualAdress+Epointeric-Eadresica;
		
		
	fseek(f, offset, SEEK_SET );
	printf("Export Table\n");
	printf("============\n");
	i=0;
	
	
		
	if(fread(&ExportTable, sizeof(ExportTable),1,f)!=1){
		printf("failed to read header\n");
	exit(1);
	}
	
	
	printf("     Export Directory\n");
	printf("     ================\n");
	
	
	printf("\t Characteristics: \t 0x%08x (phys: 0x%08x)\n", ExportTable.Characteristics,offset - ExportTable.Characteristics );
	printf("\t TimeDateStamp: \t 0x%08x\n", ExportTable.TimeDateStamp);
	printf("\t MajorVersion: \t\t 0x%08x\n", ExportTable.MajorVersion);
	printf("\t MinorVersion: \t\t 0x%08x\n", ExportTable.MinorVersion);
	printf("\t NameRVA: \t\t 0x%08x\n", ExportTable.NameRVA);
	printf("\t OrdinalBase: \t\t 0x%08x\n", ExportTable.OrdinalBase);
	printf("\t NumberOfFuncions: \t 0x%08x\n", ExportTable.NumberOfFuncions);
	printf("\t NumberOfNames: \t 0x%08x\n", ExportTable.NumberOfNames);
	printf("\t AdressTableRVA: \t\0x%08x\n", ExportTable.AdressTableRVA);
	printf("\t NamePointerTableRVA: \t 0x%08x\n", ExportTable.NamePointerTableRVA);
	printf("\t OrdinalTableRVA: \t 0x%08x\n", ExportTable.OrdinalTableRVA);
	
	
	
/*	
	printf("\t Export Adress table\n");
	printf("\t ===================\n");
	
	printf("\t   Export Directory\n");
	printf("\t   ================\n");
	for(i=0;i<ExportTable.NumberOfFuncions*4;i++){
		if(fread(&ImportThunk, sizeof(ImportThunk),1,f)!=1){
			printf("failed to read header\n");
			exit(1);
		}
	
	
		printf("\t      API: 0x%08x --> Ordinal: 0x%08x \n", offset, ImportThunk.data );

	}
	
	*/
	
	offset=offset+10*4;
	
	printf("\t   Export Adress table\n");
	printf("\t   ===================\n");
	for(i=0;i<ExportTable.NumberOfFuncions;i++){
		if(fread(&ImportThunk, sizeof(ImportThunk),1,f)!=1){
			printf("failed to read header\n");
			exit(1);
		}
	
	
		printf("\t      API: 0x%08x (phys: 0x%08x)--> Ordinal: 0x%08x \n", offset,offset-Epointeric, ImportThunk.data );
		offset+=4;
	}
	
	
	printf("\t   Export Function name table\n");
	printf("\t   ==========================\n");
	for(i=0;i<ExportTable.NumberOfNames;i++){
		if(fread(&ImportThunk, sizeof(ImportThunk),1,f)!=1){
			printf("failed to read header\n");
			exit(1);
		}
	
	
		printf("\t      API: 0x%08x --> Ordinal: 0x%08x \n", offset, ImportThunk.data );
		offset+=4;
	}
	
	
	printf("\t   Export ordinal table\n");
	printf("\t   ====================\n");
	for(i=0;i<ExportTable.NumberOfNames;i++){
		if(fread(&Ordinal, sizeof(Ordinal),1,f)!=1){
			printf("failed to read header\n");
			exit(1);
		}
	
	
		printf("\t      Value: 0x%04x  \n", Ordinal.data );
		
	}
	
	
	
	
	
	
	/*
	printf("Export Table\n");
	printf("============\n");
	printf("\t Characteristics: \t\t 0x%x\n", ExportTable.Characteristics);
	printf("\t TimeDateStamp: \t\t 0x%x\n", ExportTable.TimeDateStamp);
	printf("\t MajorVersion: \t\t 0x%x\n", ExportTable.MajorVersion);
	printf("\t MinorVersion: \t\t 0x%x\n", ExportTable.MinorVersion);
	printf("\t NameRVA: \t\t 0x%x\n", ExportTable.NameRVA);
	printf("\t OrdinalBase: \t\t 0x%x\n", ExportTable.OrdinalBase);
	printf("\t NumberOfFuncions: \t\t 0x%x\n", ExportTable.NumberOfFuncions);
	printf("\t NumberOfNames: \t\t 0x%x\n", ExportTable.NumberOfNames);
	printf("\t AdressTableRVA: \t\t 0x%x\n", ExportTable.AdressTableRVA);
	printf("\t NamePointerTableRVA: \t\t 0x%x\n", ExportTable.NamePointerTableRVA);
	printf("\t OrdinalTableRVA: \t\t 0x%x\n", ExportTable.OrdinalTableRVA);
	
	*/
	
	
	


	}








return 0;
  
}