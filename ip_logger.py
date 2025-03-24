from http.server import BaseHTTPRequestHandler, HTTPServer
import logging
import socket
import requests
import json

class RequestLogger(BaseHTTPRequestHandler):
    def do_GET(self):
        client_ip = self.client_address[0]
        logging.info(f"Incoming request from IP: {client_ip}")
        
        # Get IP Geolocation
        location_info = get_ip_location(client_ip)
        print(f"IP Logged: {client_ip} | Location: {location_info}")

        # Save to log file
        logging.info(f"IP: {client_ip} | Location: {location_info}")

        self.send_response(200)
        self.end_headers()
        self.wfile.write(b"Hello, Tor User!")

def get_server_ip():
    return socket.gethostbyname(socket.gethostname())

def get_ip_location(ip):
    try:
        # Use ipinfo.io to fetch location data
        response = requests.get(f"https://ipinfo.io/{ip}/json")
        data = response.json()
        city = data.get("city", "Unknown")
        region = data.get("region", "Unknown")
        country = data.get("country", "Unknown")
        return f"{city}, {region}, {country}"
    except Exception as e:
        print(f"Error fetching IP info: {e}")
        return "Location Unknown"

if __name__ == "__main__":
    logging.basicConfig(filename="ip_logs.txt", level=logging.INFO)

    server_ip = get_server_ip()
    port = 8080

    print(f"Server running on {server_ip}:{port}")

    server_address = ('0.0.0.0', port)
    httpd = HTTPServer(server_address, RequestLogger)
    httpd.serve_forever()
