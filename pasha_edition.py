import speech_recognition #синтезатор речи
import chess #библиотека с шахматами
import chess.engine 
from models import Stockfish #искусственый интеллект с встроенным движком
import time
import serial #передача данных через COM-PORT
import pyttsx3 #перевод текста в речь

#кушать пешку буквагдестоит|буквакудаидет|цифракудаидет

board = chess.Board()

#ser = serial.Serial("/dev/cu.usbserial-110", 9600) #Установка связи с COM-PORT
recognizer = speech_recognition.Recognizer()
microphone = speech_recognition.Microphone()
stockfish = Stockfish()
voice = pyttsx3.init()

while not board.is_stalemate() and not board.is_checkmate():
    with microphone: 
        move = ""
        recognizer.adjust_for_ambient_noise(microphone, duration=5) # шумы
        try:
            voice.say("Скажите что-нибудь")  
            voice.runAndWait()
            print("Say something!") 
            audio = recognizer.listen(microphone, 5, 5) #Прослушка микрофона
        except speech_recognition.WaitTimeoutError: #Если не рботает микрофон
            voice.say("Проверьте подключение микрофона")  
            voice.runAndWait()
            print("Can you check if your microphone is on, please?")
        try:
            voice.say("Обработка хода")  
            voice.runAndWait()
            print("Started recognition...")
            move = recognizer.recognize_google(audio, language='ru-RU').lower() #Перевод речи в текст
            move = move.split("'transcript':")[0] #Результат и возможные его вариации
        except speech_recognition.UnknownValueError:
            pass
        except speech_recognition.RequestError: #Если нет подключения к интернету
            voice.say("Проверьте подключение к интернету")  
            voice.runAndWait()
            print("Check your Internet Connection, please")
    
    
    move = move.replace('е', 'e').replace('конь', 'N').replace('слон', 'B').replace('а', 'a').replace('б',
                'b').replace('с', 'c').replace('д', 'd').replace('ф', 'f').replace('аш',
                'h').replace('эш', 'h').replace(' ', '').replace('ш', 'h').replace('жэ', 'g').replace('ж',
                'g').replace("король", "K").replace('ферзь', 'Q').replace('ладья', 'R').replace('икс', 'x') #Форматирование получившегося текста
    stockfish.set_fen_position(board.fen()) #передача текущей доски ИИ
    print(move)
    try:
        voice.say("Ваш ход" + str(board.parse_san(move)))  
        voice.runAndWait()
        print(board.parse_san(move))
        move_to_c = bytes(str(board.parse_san(move)), encoding = 'utf-8') #Перевод хода игрока в байты
        #ser.write(move_to_c) #Передача хода через COM-PORT на плату
        board.push_san(move) #Ход на виртуальной доске
        print(board)
    except:
        voice.say("Невозможный ход")  
        voice.runAndWait()
        print("Move is not correct")
        continue
    stockfish.set_fen_position(board.fen())  #Передача текущей доски ИИ
    move_to_c = bytes(str(stockfish.get_best_move()), encoding = 'utf-8') #Перевод хода ИИ в байты
    #ser.write(move_to_c) #Передача хода через COM-PORT на плату
    board.push(chess.Move.from_uci(stockfish.get_best_move())) #Ход на виртуальной доске
    print(board)
