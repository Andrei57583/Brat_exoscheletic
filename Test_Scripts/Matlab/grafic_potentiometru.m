% Cod MATLAB pentru vizualizarea graficelor potențiometrelor rotative (liniar și logaritmic)
% Ambele potențiometre de 50 kOhm

% Definirea domeniului de unghiuri (de la 0 la 300 de grade)
unghi_grade = 0:1:300; % De la 0 la 300 de grade, cu pas de 1 grad

% --- Potențiometru Liniar ---
% Rezistența totală a potențiometrului liniar
rezistenta_maxima_liniar = 50000; % 50 kOhm

% Rezistența curentă a potențiometrului liniar crește proporțional cu unghiul.
rezistenta_liniara = (unghi_grade / 300) * rezistenta_maxima_liniar;

% --- Potențiometru Logaritmic (Audio Taper) ---
% Rezistența totală a potențiometrului logaritmic
rezistenta_maxima_logaritmic = 50000; % 50 kOhm

% Factorul de curbură (taper-ul) pentru potențiometrul logaritmic
% O valoare de 2 sau 2.5 este tipică pentru un "audio taper" (logaritmic direct)
factor_curbatura = 2.5; % Puteți ajusta acest factor

% Formula pentru a genera o curbă logaritmică (similară cu un audio taper)
% Aceasta asigură că valoarea pornește de la 0 și ajunge la rezistenta_maxima_logaritmic
rezistenta_logaritmica = rezistenta_maxima_logaritmic * ( (10.^((unghi_grade/300) * factor_curbatura) - 1) / (10^factor_curbatura - 1) );


% --- Plotarea graficelor ---
figure; % Deschide o fereastră nouă pentru grafic

plot(unghi_grade, rezistenta_liniara, 'b-', 'LineWidth', 2);
hold on; % Menține graficul curent pentru a adăuga altele
plot(unghi_grade, rezistenta_logaritmica, 'r-', 'LineWidth', 2);

grid on; % Adaugă o grilă

title('Caracteristica Potențiometrelor Rotative (50 kOhm): Liniar vs. Logaritmic');
xlabel('Unghi de rotație (grade)');
ylabel('Rezistența de ieșire (Ohmi)');
legend('Potențiometru Liniar (50 kOhm)', 'Potențiometru Logaritmic (50 kOhm)');

% Ajustări vizuale
xlim([0 300]); % Setează limitele axei X
ylim([0 rezistenta_maxima_liniar * 1.1]); % Setează limitele axei Y (un pic mai sus decât maximul)
set(gca, 'FontSize', 12); % Setează dimensiunea fontului pentru axe și titluri

disp('Simularea graficelor pentru potențiometre de 50 kOhm a fost executată.');
disp('Fereastra cu graficul ar trebui să fie acum vizibilă.');