#include "server_http.hpp"
#include <iostream>
#include <typeinfo>
#include <string>
#include <utility>

#include "../core/tree.h"
// #include "../radixset.hpp"

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>


#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>
#ifdef HAVE_OPENSSL
#include "crypto.hpp"
#endif

using namespace std;
using namespace boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main() {

// clasTest radix = clasTest();



    Tree* t = new Tree();
    // crear tree con direccion a, b
    int a, b;

    HttpServer server;
    server.config.port = 8091;


    //Get | radix
    server.resource["^/radix/clear$"]["GET"] = [t](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        stringstream stream;
        SimpleWeb::CaseInsensitiveMultimap header;

        try {
          string resp = "clear";
          t->~Tree();
          stream << resp;
          response->write_get(stream,header);


        } catch (const exception &e) {
            response->write(
                SimpleWeb::StatusCode::client_error_bad_request,
                e.what()
            );
        }

    };

    //Get | radix
    server.resource["^/radix/printf$"]["GET"] = [t](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        stringstream stream;
        SimpleWeb::CaseInsensitiveMultimap header;

        try {
          string resp = "PRINTF";
          // t->~Tree();
          // cout<<"printdfs: "<<t->printdfs()<<endl;
          cout<<resp<<endl;
          stream <<t->printdfs();
          response->write_get(stream,header);


        } catch (const exception &e) {
            response->write(
                SimpleWeb::StatusCode::client_error_bad_request,
                e.what()
            );
        }

    };

/*
    //Get | radix
    server.resource["^/radix$"]["GET"] = [&radix](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        stringstream stream;
        SimpleWeb::CaseInsensitiveMultimap header;
        stream << radix.str;
        response->write_get(stream,header);

    };
*/

 /*   //Post | add polygons
    server.resource["^/radix$"]["POST"] = [&radix](
            shared_ptr<HttpServer::Response> response,
            shared_ptr<HttpServer::Request> request
        ) {

        stringstream stream;
        string json_string = "";
        SimpleWeb::CaseInsensitiveMultimap header;
        try {
            ptree pt;
            read_json(request->content, pt);
            string newcadena = pt.get<string>("cadena");
            radix.text = newcadena;

            for (boost::property_tree::ptree::value_type& rowPair:pt.get_child("polygon")) {
                for (boost::property_tree::ptree::value_type& itemPair : rowPair.second) {
                    int value = itemPair.second.get_value<int>();
                    v.push_back(value);
                }
            }
            for (size_t i = 0; i < v.size(); i += 2) {
                P point(v[i], v[i+1]);
                pv.push_back(point);
            }
            int identifier_polygon = count++;
            tree->insert(new Polygon<dtype>(pv, identifier_polygon));
            json_string = "{\"status\": true}";
            json_string = "{\"status\": true}";
            // json_string += "{ cadena: " + radix.respuestaHola(word) + "}";
            stream << json_string;
            response->write_get(stream,header);
        } catch (const exception &e) {
            response->write(
                SimpleWeb::StatusCode::client_error_bad_request,
                e.what()
            );
        }
    };*/


    /* http://localhost:8091/radix/getTree?word=test */
    server.resource["^/radix/getTree$"]["GET"] = [t,&a,&b](
        shared_ptr<HttpServer::Response> response,
        shared_ptr<HttpServer::Request> request
        ) {

        stringstream stream;
        SimpleWeb::CaseInsensitiveMultimap header;

        // capturar dato string para consulta
        try {
            string word;
            auto query_fields = request->parse_query_string();
            for(auto &field : query_fields)
                word = field.second;

            //llamado a la funcion del tree
            t->add(word, a, b);
            // convertir a stream text para envio
            cout<<t->printjson()<<endl;

            stream << t->printjson();
            //envio de la respuesta
            response->write_get(stream, header);


        } catch (const exception &e) {
            response->write(
                SimpleWeb::StatusCode::client_error_bad_request,
                e.what()
            );
        }
    };

    /* http://localhost:8091/radix/find?word=test */
    server.resource["^/radix/find$"]["GET"] = [t,&a,&b](
        shared_ptr<HttpServer::Response> response,
        shared_ptr<HttpServer::Request> request
        ) {

        stringstream stream;
        SimpleWeb::CaseInsensitiveMultimap header;

        try {
            string word;
            auto query_fields = request->parse_query_string();
            for(auto &field : query_fields)
                word = field.second;


             cout<<"FIND INPUT: "<< word <<endl;

            // stream << radix.test(word);
            stream << t->find(word);

            response->write_get(stream, header);


        } catch (const exception &e) {
            response->write(
                SimpleWeb::StatusCode::client_error_bad_request,
                e.what()
            );
        }
    };


    /* http://localhost:8091/radix/delete?word=test */
    server.resource["^/radix/delete$"]["GET"] = [t,&a,&b](
        shared_ptr<HttpServer::Response> response,
        shared_ptr<HttpServer::Request> request
        ) {

        stringstream stream;
        SimpleWeb::CaseInsensitiveMultimap header;

        try {
            string word;
            auto query_fields = request->parse_query_string();
            for(auto &field : query_fields)
                word = field.second;


             cout<<"DELETE INPUT: "<< word <<endl;

            // eliminar la palabra
            t->erase(word);

            stream <<t->printjson();

            response->write_get(stream, header);


        } catch (const exception &e) {
            response->write(
                SimpleWeb::StatusCode::client_error_bad_request,
                e.what()
            );
        }
    };



    server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
        // manejo de errores
        // Notar que la connexion  hace timeouts  tambien llama  y maneja la modificacion del  SimpleWeb::errc::operation_canceled
    };

    cout << "WEB SERVER IS RUNNNING" << endl;
    thread server_thread([&server]() {
        // Start server
        server.start();
    });

    // Esperar al servicio para iniciar asi el cliente se conecta
    this_thread::sleep_for(chrono::seconds(1));
    server_thread.join();
}
