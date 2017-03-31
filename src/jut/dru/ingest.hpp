/** @file jut/dru/ingest.hpp Schema for Druid ingestion spec.
 * @see http://druid.io/docs/latest/ingestion/index.html
 */

#ifndef JUT_DRU_INGEST_INCLUDED
#define JUT_DRU_INGEST_INCLUDED

// Local
#include "jut/dat/either.hpp"

// C++ standard
#include <string>
#include <vector>

namespace jut { // Jeff's UTilitites
namespace dru { // DRUid

    using jut::dat::either;

    using std::string;
    using std::vector;

    /** @see http://druid.io/docs/latest/querying/granularities.html */
    struct granularity_spec_t {
        string type = "uniform";
        string segment_granularity = "DAY";
        string query_granularity = "NONE";
        bool   rollup = true;
        string intervals;
    };

    struct extraction_fn_t {
        string type;
        int index;
        int length;
    };

    struct complex_field_t {
        string type;    // e.g., "extraction"
        string dimension;
        string output_name;
        extraction_fn_t extraction_fn;
    };

    /** Required fields depend on `type`.
     * @see http://druid.io/docs/latest/querying/aggregations.html
     */
    struct aggregator_t {
        string                                  type;
        string                                  name;
        string                                  field_name;
        vector<string>                          field_names;
        string                                  fn_aggregate;
        string                                  fn_combine;
        string                                  fn_reset;
        vector<either<string, complex_field_t>> fields;
        bool by_row =                           false;
    };

    /** Supports geographic queries. */
    struct spatial_dimension_t {
        string         dim_name;
        vector<string> dims;
    };

    /** If `dimensions` is empty, Druid considers all columns except timestamp
     * and metrics to be dimensions.
     */
    struct dimensions_spec_t {
        vector<string>              dimensions;
        vector<string>              dimension_exclusions;
        vector<spatial_dimension_t> spatial_dimensions;
    };

    struct timestamp_spec_t {
        string column;
        string format = "auto";
    };

    struct field_t {
        string type;    // "root" or "path"
        string name;
        string expr;    // uses JsonPath notation
    };

    struct flatten_spec_t {
        bool            use_field_discovery = true;
        vector<field_t> fields;
    };

    /** Different `format` values require different fields be set. */
    struct parse_spec_t {
        string              format = "tsv";             // all
        timestamp_spec_t    timestamp_spec;             // all
        dimensions_spec_t   dimensions_spec;            // all
        flatten_spec_t      flatten_spec;               // json
        string              delimiter = "\t";           // tsv
        string              list_delimiter = "\x01";    // csv, tsv
        vector<string>      columns;                    // csv, tsv
    };

    /** `type` may be string, hadoopyString, protobuf, or an extension.
     * The set of fields required by `parse_spec` depends on `type`.
     * @see http://druid.io/docs/latest/development/extensions.html
     */
    struct parser_t {
        std::string     type = "string";
        parse_spec_t    parse_spec;
    };

    struct data_schema_t {
        std::string             name;
        parser_t                parser;
        vector<aggregator_t>    metrics_spec;
        granularity_spec_t      granularity_spec;
    };

    struct ingestion_spec {
        data_schema_t   data_schema;
        io_config_t     io_config;
        tuning_config_t tuning_config;
    };
}
}

#endif
