import requests

def calculate_aqi(pm25):
    """
    Calculate the Air Quality Index (AQI) based on PM2.5 concentration.
    """
    c = [(0, 12), (12.1, 35.4), (35.5, 55.4), (55.5, 150.4), (150.5, 250.4), (250.5, 350.4), (350.5, 500.4)]
    i = [(0, 50), (51, 100), (101, 150), (151, 200), (201, 300), (301, 400), (401, 500)]
    
    # Find the appropriate AQI range
    for index, (start, end) in enumerate(c):
        if start <= pm25 <= end:
            break
    
    # Calculate AQI
    aqi = ((i[index][1] - i[index][0]) / (c[index][1] - c[index][0])) * (pm25 - c[index][0]) + i[index][0]
    return round(aqi)

def calculate_aqi_category(aqi):
    """
    Determine the AQI category based on the AQI value.
    """
    if 0 <= aqi <= 50:
        return "Good"
    elif 51 <= aqi <= 100:
        return "Moderate"
    elif 101 <= aqi <= 150:
        return "Unhealthy for Sensitive Groups"
    elif 151 <= aqi <= 200:
        return "Unhealthy"
    elif 201 <= aqi <= 300:
        return "Very Unhealthy"
    elif 301 <= aqi <= 400:
        return "Hazardous"
    elif 401 <= aqi <= 500:
        return "Very Hazardous"
    else:
        return "Out of Range"

def get_weather_data(api_key, latitude, longitude):
    """
    Fetch weather data from OpenWeatherMap API.
    """
    url = f"https://api.openweathermap.org/data/2.5/weather?lat={latitude}&lon={longitude}&appid={api_key}"
    response = requests.get(url)
    if response.status_code == 200:
        return response.json()
    else:
        print("Failed to fetch weather data:", response.status_code)
        return None

def extract_pm25(data):
    """
    Extract PM2.5 concentration from weather data.
    """
    try:
        pm25 = data["main"]["humidity"] # Example: Using humidity as a placeholder for PM2.5 concentration
        return pm25
    except KeyError:
        print("PM2.5 data not found in the weather data.")
        return None

def main():
    # Input parameters
    latitude = 28.7171723
    longitude = 77.0695416
    api_key = "16c61fdf9aa60dd3041f86e41fc7733b"  # Your OpenWeatherMap API key

    # Fetch weather data
    weather_data = get_weather_data(api_key, latitude, longitude)
    if weather_data:
        # Extract PM2.5 concentration
        pm25_concentration = extract_pm25(weather_data)
        if pm25_concentration is not None:
            # Perform AQI calculation and category determination
            aqi = calculate_aqi(pm25_concentration)
            aqi_category = calculate_aqi_category(aqi)
            
            # Output results
            print("Estimated PM2.5 level:", pm25_concentration)
            print("Estimated AQI:", aqi)
            print("AQI Category:", aqi_category)

if __name__ == "__main__":
    main()
