import http.server
import socketserver
import json
import requests

PORT = 8080  # Change if needed

class MyHandler(http.server.SimpleHTTPRequestHandler):
    def log_request_info(self, client_ip):
        print(f"Incoming request from: {client_ip}")

        # Get IP Geolocation
        try:
            response = requests.get(f"http://ip-api.com/json/{client_ip}")
            data = response.json()

            if data["status"] == "success":
                location_info = f"{data['city']}, {data['country']} (Lat: {data['lat']}, Lon: {data['lon']})"
                print(f"IP Location: {location_info}")
                return location_info
            else:
                return "Location Not Found"
        except Exception as e:
            print(f"Error fetching location: {e}")
            return "Error Fetching Location"

    def do_GET(self):
        client_ip = self.client_address[0]
        location_info = self.log_request_info(client_ip)

        # Respond with IP & Location
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        self.wfile.write(f"Your IP: {client_ip}\nLocation: {location_info}\n".encode())

with socketserver.TCPServer(("", PORT), MyHandler) as httpd:
    print(f"Serving at port {PORT}")
    httpd.serve_forever()
