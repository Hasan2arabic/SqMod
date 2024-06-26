//
// ResultMetadata.h
//
// Library: Data/MySQL
// Package: MySQL
// Module:  ResultMetadata
//
// Definition of the ResultMetadata class.
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Data_MySQL_ResultMetadata_INCLUDED
#define Data_MySQL_ResultMetadata_INCLUDED


#include "Poco/Data/MetaColumn.h"
#if defined(__MINGW32__) || defined(__MINGW64__)
	#include <mysql/mysql.h>
#else
	#include <mysql.h>
#endif
#include <vector>


#if LIBMYSQL_VERSION_ID >= 80000
typedef bool my_bool;  // Workaround to make library work with MySQL client 8.0 as well as earlier versions
typedef char my_boolv; // Workaround for std::vector<bool>
#else
typedef my_bool my_boolv;
#endif


namespace Poco {
namespace Data {
namespace MySQL {


class ResultMetadata
	/// MySQL result metadata
{
public:
	~ResultMetadata();
		/// Destroys the ResultMetadata.

	void reset();
		/// Resets the metadata.

	void init(MYSQL_STMT* stmt);
		/// Initializes the metadata.

	std::size_t columnsReturned() const;
		/// Returns the number of columns in resultset.

	const MetaColumn& metaColumn(std::size_t pos) const;
		/// Returns the reference to the specified metacolumn.

	MYSQL_BIND* row();
		/// Returns pointer to native row.

	std::size_t length(std::size_t pos) const;
		/// Returns the length.

	const unsigned char* rawData(std::size_t pos) const;
		/// Returns raw data.

	bool isNull(std::size_t pos) const;
		/// Returns true if value at pos is null.

	void adjustColumnSizeToFit(std::size_t pos);
		/// Expands the size allocated for column to fit the length of the data.

private:
	void freeMemory();

	std::vector<MetaColumn>    _columns;
	std::vector<MYSQL_BIND>    _row;
	std::vector<char*>         _buffer;
	std::vector<unsigned long> _lengths;
	std::vector<my_boolv>      _isNull; // using char instead of bool to avoid std::vector<bool> disaster
};


} } } // namespace Poco::Data::MySQL


#endif //Data_MySQL_ResultMetadata_INCLUDED
