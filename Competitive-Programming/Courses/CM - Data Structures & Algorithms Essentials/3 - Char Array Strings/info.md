## Char Arrays

- Syntax for initialization:

```cpp

char a[100] = {'a','b','c'};         // WRONG - Will print garbage value
char a[100] = {'a','b','c', '\0'};   // RIGHT
char a[100] = "abc";                // Another way
char a[] = "abc";                // Another way
```

- Length of Array:

```cpp
cout << strlen(a);      // will print size of array i.e. no of visible characters
cout << sizeof(a);       // +1 because of null character
```

- Basic Input

```cpp
// Problem with cin is that it only takes first word. Ex: in 'hello world' only 'hello' will be considered
char a[100];
cin >> a;

```

- **cin.get()**: It reads one character at a time

```cpp

char sentence[1000];
char temp = cin.get();
int len = 0;

while(temp!='\n')
{
    // Can add adittional check to see if len < 1000
    sentence[len++] = temp;
    temp=cin.get();
}
sentence[len]='\0';
cout<<sentence;
```

- **cin.getline()**: To input entire sentence

```cpp

char sentence[1000];
cin.getline(sentence, 1000);    // 2nd argument is to tell how many characters it can hold

cout << sentence;


// 3rd argument (optional) is to tell when to stop reading input. By default it is  '\n'
cin.getline(sentence, 1000, '#');
```

- This may sometimes cause an **ERROR**, so remember:

```cpp
int n;
cin >> n;

// We used this to get '/n' thats pressed after getting 'n' else the first value in cin.getline will be '/n'
cin.get(); // Or run below loop one more time

char sentence[1000];

while (n--)
{
    cin.getline(sentence, 1000);
    cout << sentence << endl;
}
```

## Methods

- **strlen()**: Find length of string

```cpp
char a[1000] = "apple";
cout << strlen(a);
```

- **strcpy()**: Copy a string into another

```cpp
char a[1000] = "apple";
char b[1000];
cout << strcpy(b,a);    // First one is destination, Next one is source
```

- **strcmp()**: Compare two strings

```cpp
char a[1000] = "apple";
char b[1000];
strcpy(b,a);
cout << strcmp(a,b);    // If everything matches returns 0, else something negative or positive
```

- **strcat()**: Concat two strings

```cpp
char web[] = "www.";
char domain[] = "google.com"
cout << strcat(web,domain);

```

## Strings

- String class

```cpp

string s = "hello world";   // Dynamic Array

```

- Input:

```cpp

string s;
getline(cin,s);
getline(cin,s, '.');        // 3rd optional character is used to tell when to stop input. Delimitter

```

- String array

```cpp

int n = 5;
vector<string> sarr;
string temp;
while(n--){
    getline(cin,temp);
    sarr.push_back(temp);
}
```

- Length of string

```cpp

string s = "abcd";
cout << s.length();
```

- Convert `int` into `string`

```cpp

int c = 15;

string s;
s += to_string(c);

```
