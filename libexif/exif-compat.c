/* exif-compat.c
*
* Copyright (c) 2014 The OmniROM Project
*                    The CyanogenMod Project
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the
* Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301 USA.
*/

#include <jhead.h>

#include <dlfcn.h>

#define LIBPATH "libjhead.so"

ImageInfo_t ImageInfo;

static Section_t * Sections = NULL;
static int SectionsAllocated;
static int SectionsRead;
static int HaveAll;


// Compatibility functions which call the according functions from libjhead
void ErrFatal(char * msg) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*err)(char*);
	err = dlsym(handle, "ErrFatal");
	(*err)(msg);
	dlclose(handle);
}

void ErrNonfatal(char * msg, int a1, int a2) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*err)(char*, int, int);
	err = dlsym(handle, "ErrNonfatal");
	(*err)(msg, a1, a2);
	dlclose(handle);
}

void FileTimeAsString(char * TimeStr) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*ft)(char*);
	ft = dlsym(handle, "FileTimeAsString");
	(*ft)(TimeStr);
	dlclose(handle);
}

int Exif2tm(struct tm * timeptr, char * ExifTime) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*exif)(struct tm*, char*);
	exif = dlsym(handle, "Exif2tm");
	int out = (*exif)(timeptr, ExifTime);
	dlclose(handle);
	return out;
}

void process_EXIF(unsigned char * CharBuf, unsigned int length) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*process)(unsigned char*, unsigned int);
	process = dlsym(handle, "process_EXIF");
	(*process)(CharBuf, length);
	dlclose(handle);
}

int RemoveThumbnail(unsigned char * ExifSection) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*remove)(unsigned char*);
	remove = dlsym(handle, "RemoveThumbnail");
	int out = (*remove)(ExifSection);
	dlclose(handle);
	return out;
}

void ShowImageInfo(int ShowFileInfo) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*show)(int);
	show = dlsym(handle, "ShowImageInfo");
	(*show)(ShowFileInfo);
	dlclose(handle);
}

void ShowConciseImageInfo(void) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*show)(void);
	show = dlsym(handle, "ShowConciseImageInfo");
	(*show)();
	dlclose(handle);
}

const char * ClearOrientation(void) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	const char* (*clear)(void);
	clear = dlsym(handle, "ClearOrientation");
	const char* out = (*clear)();
	dlclose(handle);
	return out;
}

void PrintFormatNumber(void * ValuePtr, int Format, int ByteCount) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*print)(void*, int, int);
	print = dlsym(handle, "PrintFormatNumber");
	(*print)(ValuePtr, Format, ByteCount);
	dlclose(handle);
}

double ConvertAnyFormat(void * ValuePtr, int Format) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	double (*get)(void*, int);
	get = dlsym(handle, "ConvertAnyFormat");
	double out = (*get)(ValuePtr, Format);
	dlclose(handle);
	return out;
}

int Get16u(void * Short) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*get)(void*);
	get = dlsym(handle, "Get16u");
	int out = (*get)(Short);
	dlclose(handle);
	return out;
}

unsigned Get32u(void * Long) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	unsigned (*get)(void*);
	get = dlsym(handle, "Get32u");
	unsigned out = (*get)(Long);
	dlclose(handle);
	return out;
}

int Get32s(void * Long) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*get)(void*);
	get = dlsym(handle, "Get32s");
	int out = (*get)(Long);
	dlclose(handle);
	return out;
}

void Put32u(void * Value, unsigned PutValue) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*put)(void*, unsigned);
	put = dlsym(handle, "Put32u");
	(*put)(Value, PutValue);
	dlclose(handle);
}

void create_EXIF(ExifElement_t* elements, int exifTagCount, int gpsTagCount,
		int hasDateTimeTag) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*create)(ExifElement_t*, int, int, int);
	create = dlsym(handle, "create_EXIF");
	(*create)(elements, exifTagCount, gpsTagCount, hasDateTimeTag);
	dlclose(handle);
}

int TagNameToValue(const char* tagName) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*tag)(const char*);
	tag = dlsym(handle, "TagNameToValue");
	int out = (*tag)(tagName);
	dlclose(handle);
	return out;
}

int IsDateTimeTag(unsigned short tag) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*date)(unsigned short);
	date = dlsym(handle, "IsDateTimeTag");
	int out = (*date)(tag);
	dlclose(handle);
	return out;
}

extern void ProcessMakerNote(unsigned char * DirStart, int ByteCount,
		unsigned char * OffsetBase, unsigned ExifLength) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*note)(unsigned char*, int, unsigned char*, unsigned);
	note = dlsym(handle, "ProcessMakerNote");
	(*note)(DirStart, ByteCount, OffsetBase, ExifLength);
	dlclose(handle);
}

void ProcessGpsInfo(unsigned char * ValuePtr, int ByteCount,
		unsigned char * OffsetBase, unsigned ExifLength) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*info)(unsigned char*, int, unsigned char*, unsigned);
	info = dlsym(handle, "ProcessGpsInfo");
	(*info)(ValuePtr, ByteCount, OffsetBase, ExifLength);
	dlclose(handle);
}

int IsGpsTag(const char* tag) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*gps)(const char*);
	gps = dlsym(handle, "IsGpsTag");
	int out = (*gps)(tag);
	dlclose(handle);
	return out;
}

int GpsTagToFormatType(unsigned short tag) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*gps)(unsigned short);
	gps = dlsym(handle, "GpsTagToFormatType");
	int out = (*gps)(tag);
	dlclose(handle);
	return out;
}

int GpsTagNameToValue(const char* tagName) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*gps)(const char*);
	gps = dlsym(handle, "GpsTagNameToValue");
	int out = (*gps)(tagName);
	dlclose(handle);
	return out;
}

TagTable_t* GpsTagToTagTableEntry(unsigned short tag) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	TagTable_t* (*gps)(unsigned short);
	gps = dlsym(handle, "GpsTagToTagTableEntry");
	TagTable_t* out = (*gps)(tag);
	dlclose(handle);
	return out;
}

int ReadJpegSections(FILE * infile, ReadMode_t ReadMode) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*reset)(FILE*, ReadMode_t);
	reset = dlsym(handle, "ReadJpegSections");
	int out = (*reset)(infile, ReadMode);
	dlclose(handle);
	return out;
}

void DiscardData(void) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*discard)(void);
	discard = dlsym(handle, "DiscardData");
	(*discard)();
	dlclose(handle);
}

void DiscardAllButExif(void) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*discard)(void);
	discard = dlsym(handle, "DiscardAllButExif");
	(*discard)();
	dlclose(handle);
}

int ReadJpegFile(const char * FileName, ReadMode_t ReadMode) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*read)(const char*, ReadMode_t);
	read = dlsym(handle, "ReadJpegFile");
	int out = (*read)(FileName, ReadMode);
	dlclose(handle);
	return out;
}

int ReplaceThumbnail(const char * ThumbFileName) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*replace)(const char*);
	replace = dlsym(handle, "ReplaceThumbnail");
	int out = (*replace)(ThumbFileName);
	dlclose(handle);
	return out;
}

int ReplaceThumbnailFromBuffer(const char* Thumb, int ThumbLen) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*replace)(const char*, int);
	replace = dlsym(handle, "ReplaceThumbnailFromBuffer");
	int out = (*replace)(Thumb, ThumbLen);
	dlclose(handle);
	return out;
}

int SaveThumbnail(char * ThumbFileName) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*save)(char*);
	save = dlsym(handle, "SaveThumbnail");
	int out = (*save)(ThumbFileName);
	dlclose(handle);
	return out;
}

int RemoveSectionType(int SectionType) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*remove)(int);
	remove = dlsym(handle, "RemoveSectionType");
	int out = (*remove)(SectionType);
	dlclose(handle);
	return out;
}

int RemoveUnknownSections(void) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*remove)(void);
	remove = dlsym(handle, "RemoveUnknownSections");
	int out = (*remove)();
	dlclose(handle);
	return out;
}

int WriteJpegFile(const char * FileName) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*write)(const char*);
	write = dlsym(handle, "WriteJpegFile");
	int out = (*write)(FileName);
	dlclose(handle);
	return out;
}

Section_t * FindSection(int SectionType) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	Section_t* (*fs)(int);
	fs = dlsym(handle, "FindSection");
	Section_t* out = (*fs)(SectionType);
	dlclose(handle);
	return out;
}

Section_t * CreateSection(int SectionType, unsigned char * Data, int size) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	Section_t* (*cs)(int, unsigned char*, int);
	cs = dlsym(handle, "CreateSection");
	Section_t* out = (*cs)(SectionType, Data, size);
	dlclose(handle);
	return out;
}

void ResetJpgfile(void) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	void (*reset)(void);
	reset = dlsym(handle, "ResetJpgfile");
	(*reset)();
	dlclose(handle);
}

int ReadJpegSectionsFromBuffer(unsigned char* buffer, unsigned int buffer_size,
		ReadMode_t ReadMode) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*read)(unsigned char*, unsigned int, ReadMode_t);
	read = dlsym(handle, "ReadJpegSectionsFromBuffer");
	int out = (*read)(buffer, buffer_size, ReadMode);
	dlclose(handle);
	return out;
}

int WriteJpegToBuffer(unsigned char* buffer, unsigned int buffer_size) {
	void *handle = dlopen(LIBPATH, RTLD_LAZY);
	int (*write)(unsigned char*, unsigned int);
	write = dlsym(handle, "WriteJpegToBuffer");
	int out = (*write)(buffer, buffer_size);
	dlclose(handle);
	return out;
}
