import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from matplotlib.lines import Line2D
from matplotlib.patches import Patch

def print_message(data, message, a):
    for i, j in data.iterrows():
        gare_depart = j['Departure station']
        gare_arrivee = j['Arrival station']
        message += f"Gare de départ : {gare_depart} -> Gare d'arrivée : {gare_arrivee}"
    if (a == 1):
        message += f", ({data["Pct cancel"].max()} %)\n\n"
        st.error(message)
    if (a == 0):
        message += f", ({data["Pct cancel"].min()} %)\n\n"
        st.success(message)
    return 0

st.set_page_config(page_title="Prédiction Retards SNCF", layout="wide", page_icon="image/tardis.png")
st.sidebar.image("image/tardis.png", width=200)
st.sidebar.title("Navigation")
data = pd.read_csv("cleaned_dataset.csv")
st.sidebar.markdown("---")

page = st.sidebar.radio(
    "Menu",
    ["Accueil", "Carte", "Analyse", "Modèle", "Auteur"]
)

if page == "Accueil":
    col1, col2, col3 = st.columns([1, 3, 1])
    with col2:
        st.markdown("<h1 style='text-align: center; color: #6C3483;'>Bienvenue sur <span style='color:#BB8FCE;'>TARDIS</span> !</h1>", unsafe_allow_html=True)
    st.markdown("")
    col_texte, col_image = st.columns([2, 1])
    with col_texte:
        st.markdown("""
        <h3 style='color: #6C3483;'>TARDIS, c’est quoi ?</h3>
        <ul style='font-size: 18px; color: #4A235A;'>
            <li>Une <b>carte interactive</b> pour localiser les gares SNCF</li>
            <li>Une <b>analyse détaillée</b> des retards, annulations et causes</li>
            <li>Un <b>modèle de prédiction</b> de retard pour vos trajets</li>
            <li>Des <b>statistiques visuelles</b> pour mieux comprendre le trafic</li>
        </ul>
        """, unsafe_allow_html=True)
    with col_image:
        st.image("image/train_sncf.jpg", use_container_width=True)
    st.markdown("<hr>", unsafe_allow_html=True)
    nom = st.text_input("Quel est ton nom ?")
    age = st.slider("Quel âge avez vous ?", 0, 100, 25)
    if nom:
        st.success(f"Bonjour {nom} ({age} ans), bienvenue à bord de TARDIS ?")
    st.markdown("""<div style='background-color: #F5EEF8; padding: 10px; border-radius: 10px; text-align: center;'>
        📣 <b style='color: #6C3483;'>Conseil :</b> Navigue via le menu à gauche pour découvrir les différentes fonctionnalités. </div>
    """, unsafe_allow_html=True)
    st.markdown("---")
    st.caption("Chez nous, être en retard, c’est juste arriver avant d’être parti !")

elif page == "Carte":
    st.title("Carte des Gares TARDIS avec filtre de retard")
    data_map = pd.read_csv("stations_sncf.csv")
    data_map = data_map.dropna(subset=['latitude', 'longitude'])
    max_limit = st.slider(
        "Afficher les gares avec un retard moyen inférieur ou égal à :", 
        min_value=0.0, 
        max_value=20.0, 
        value=10.0, 
        step=0.2
    )
    filtered_data = data_map[(data_map["retard_moyen"] > 0) & (data_map["retard_moyen"] <= max_limit)]
    if filtered_data.empty:
        st.warning("Aucune gare avec un retard moyen dans cette plage.")
    else:
        st.map(filtered_data[['latitude', 'longitude']])
        st.caption(f"{len(filtered_data)} gares affichées avec un retard moyen ≤ {max_limit:.1f} min.")
    st.markdown("---")
    st.caption("Hier, aujourd’hui et demain ne sont que des arrêts sur notre ligne !")

elif page=="Analyse":
    st.title("Voici plusieurs informations à propos des trains")
    data_positif = data[(data["Pct cancel"] >= 0)]
    data_cancel = data_positif["Pct cancel"]
    st.subheader("Statistiques globales des trains (Janvier 2018 - Décembre 2024)")

    col1, col2 = st.columns(2)
    with col1:
        st.markdown("**Nombre total de trains programmés :**")
        st.markdown(f"<h3 style='color:#00416A'>{int(data_positif['Number train active'].sum()):,}".replace(",", " ") + "</h3>", unsafe_allow_html=True)

        st.markdown("**Nombre total de trains annulés :**")
        st.markdown(f"<h3 style='color:#C20000'>{int(data_positif['Number of cancelled trains'].sum()):,}".replace(",", " ") + "</h3>", unsafe_allow_html=True)

        st.markdown("**Taux moyen d’annulation :**")
        st.markdown(f"<h3 style='color:#E67E22'>{data_cancel.mean().round(2)} %</h3>", unsafe_allow_html=True)

    with col2:
        st.markdown("**Taux moyen de retards au départ :**")
        st.markdown(f"<h3 style='color:#2980B9'>{data_positif['Pct depart delay rate'].mean().round(2)} %</h3>", unsafe_allow_html=True)

        st.markdown("**Taux moyen de retards à l’arrivée :**")
        st.markdown(f"<h3 style='color:#8E44AD'>{data_positif['Pct arrival delay rate'].mean().round(2)} %</h3>", unsafe_allow_html=True)

    st.markdown("---")

    plus_de_cancel = data_positif[data_cancel == data_cancel.max()]
    dates = plus_de_cancel["Date"].unique()
    dates_str = ", ".join(dates)
    message_n = (f"Pourcentage le plus élevé de trains annulés:\n\n[{dates_str}] ")
    print_message(plus_de_cancel, message_n, 1)

    moins_de_cancel = data_positif[data_cancel == data_cancel.min()]
    dates = moins_de_cancel["Date"].unique()
    dates_str = ", ".join(dates)
    message_p = (f"Pourcentage le plus bas de train annulés:\n\n[{dates_str}] ")
    print_message(moins_de_cancel, message_p, 0)
    
    st.subheader("Statistiques mensuelles détaillées")
    mois = pd.date_range("2018-01-01", "2024-12-01", freq="MS").strftime("%Y-%m").tolist()
    date = st.select_slider("Sélectionnez un mois :", options=mois, value="2020-01")
    st.markdown(f"**Mois sélectionné :** {date}")
    data_mont = data[data["Date"] == date]
    data_cancel = data_mont[data_mont["Pct cancel"] >= 0]["Pct cancel"]
    col1, col2 = st.columns(2)

    with col1:
        total_trains = int(data_mont["Number train active"].sum())
        moyenne_trains = data_mont["Number train active"].mean().round(0) if "Number train active" in data_mont.columns else None
        annulation_pct = data_cancel.mean().round(2)

        st.markdown("**Nombre total de trains actifs :**")
        st.markdown(f"<h4 style='color:#00416A'>{total_trains:,}".replace(",", " ") + "</h4>", unsafe_allow_html=True)

        st.markdown("**Nombre moyen de trains par gare :**")
        if moyenne_trains:
            st.markdown(f"<h4 style='color:#2980B9'>{moyenne_trains:.0f}</h4>", unsafe_allow_html=True)
        else:
            st.markdown("<i>Donnée indisponible</i>", unsafe_allow_html=True)

        st.markdown("**Taux d’annulation moyen :**")
        st.markdown(f"<h4 style='color:#C0392B'>{annulation_pct} %</h4>", unsafe_allow_html=True)

    with col2:
        retard_depart = data_mont["Pct depart delay rate"].mean().round(2)
        retard_arrivee = data_mont["Pct arrival delay rate"].mean().round(2)

        st.markdown("**Taux moyen de retard au départ :**")
        st.markdown(f"<h4 style='color:#E67E22'>{retard_depart} %</h4>", unsafe_allow_html=True)

        st.markdown("**Taux moyen de retard à l’arrivée :**")
        st.markdown(f"<h4 style='color:#8E44AD'>{retard_arrivee} %</h4>", unsafe_allow_html=True)

    st.markdown("---")
            
    st.write("## Ici vous pouvez voir des données sur une gare:")
    station = st.selectbox("Veuillez choisir votre gare", sorted(data['Departure station'].unique()))
    annees = list(range(2018, 2025))
    mois = [f"{i:02d}" for i in range(1, 13)]
    annee = st.selectbox("Choisissez l'année", annees)
    mois_selection = st.selectbox("Choisissez le mois", mois)
    date = f"{annee}-{mois_selection}"
    st.write(f"Date sélectionnée : {date}")
    values = ((data_positif["Date"] == date) & ((data_positif["Departure station"] == station) | (data_positif["Arrival station"] == station)))
    data_gare = data_positif[values]
    if not data_gare.empty:
        st.write("### Résultats pour la station sélectionnée :")
        st.markdown("Si une donnée vaut -1, cela signifie qu'elle est manquante")
        st.dataframe(data_gare[["Date", "Departure station", "Arrival station", "Number of scheduled trains", "Number of cancelled trains",
            "Pct cancel", "Pct depart delay rate", "Pct arrival delay rate"]])
    else:
        st.warning("Aucune donnée disponible pour cette station à cette date.")
        
    st.write("## Graphiques :")
    st.write("### Taux de retards et d'annulation par mois")
    monthly_stats = data.groupby("Date").agg({"Pct cancel": "mean","Pct depart delay rate": "mean","Pct arrival delay rate": "mean"})
    monthly_stats.rename(columns={"Pct cancel": "Pourcentage d'annulation", "Pct depart delay rate": "Taux de retard au départ", "Pct arrival delay rate": "Taux de retard à l'arrivée"}, inplace=True)
    st.line_chart(monthly_stats)
    delay_severe = data_positif.groupby("Severe delay rate")["Date"]
    delay_severe = data_positif.groupby("Date")["Severe delay rate"].mean().sort_index()
    st.write("### Taux de retards sévères par mois")
    st.line_chart(delay_severe)
    st.write("### Corrélations entre les variables numériques")
    fig, ax = plt.subplots()
    cause_cols = [
        "Pct delay due to external causes",
        "Pct delay due to infrastructure",
        "Pct delay due to traffic management",
        "Pct delay due to rolling stock",
        "Pct delay due to station management and equipment reuse",
        "Pct delay due to passenger handling (crowding, disabled persons, connections)"
    ]
    data_numeric = data_positif[cause_cols].copy()
    data_numeric.rename(columns={"Pct delay due to external causes": "Retard - Causes externes", "Pct delay due to infrastructure": "Retard - Infrastructure",
    "Pct delay due to traffic management": "Retard - Gestion du trafic", "Pct delay due to rolling stock": "Retard - Matériel roulant",
    "Pct delay due to station management and equipment reuse": "Retard - Gestion station", 
    "Pct delay due to passenger handling (crowding, disabled persons, connections)": "Retard - Gestion passagers"}, inplace=True)
    sns.heatmap(data_numeric.corr(), annot=True, ax=ax)
    st.pyplot(fig)

    st.write("### Boxplot : Retard moyen au départ")
    fig2, ax2 = plt.subplots(figsize=(8, 6))

    sns.boxplot(
        y=data_positif["Average delay of all trains at departure"].dropna().head(1000),
        ax=ax2,
        width=0.5,
        flierprops={"marker": "o", "markersize": 6, "markerfacecolor": "red"},
        boxprops=dict(facecolor='lightgray', edgecolor='black')
    )

    ax2.set_ylabel("Minutes de retard", fontsize=12)
    ax2.grid(True, linestyle="--", alpha=0.6)

    legend_elements = [
        Patch(facecolor='lightgray', edgecolor='black', label='Données les plus fréquentes'),
        Line2D([0], [0], color='black', lw=2, label='Médiane'),
        Line2D([0], [0], marker='o', color='w', label='Données moins fréquentes',
               markerfacecolor='red', markersize=6)
    ]
    ax2.legend(handles=legend_elements, loc='upper right')

    st.pyplot(fig2)

    st.markdown("""---""")
    st.caption("En avance sur le passé, en retard sur le futur – mais toujours pile à l'heure !")

elif page == "Modèle":
    st.title("Prédiction des retards des trains pour l'année 2026")
    st.markdown("---")
    @st.cache_data
    
    def load_data():
        data = pd.read_csv("predictions.csv")
        data["Month"] = pd.to_datetime(data["Month"], format="%Y-%m")
        data["Year"] = data["Month"].dt.year
        data["Month_Num"] = data["Month"].dt.month
        data["Month_Label"] = data["Month_Num"].apply(lambda x: ["Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"][x-1])
        return data

    data = load_data()
    st.header("Faites une prédiction personnalisée")
    col1, col2 = st.columns(2)

    with col1:
        departure_station = st.selectbox("Gare de départ", sorted(data["Departure station"].unique()))
    with col2:
        possible_arrivals = data[data["Departure station"] == departure_station]["Arrival station"].unique()
        arrival_station = st.selectbox("Gare d'arrivée", sorted(possible_arrivals))

    selected_month_label = st.selectbox("Choisissez un mois", data["Month_Label"].unique())
    month_map = dict(zip(["Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"], range(1, 13)))
    selected_month_num = month_map[selected_month_label]

    if st.button("🔍 Prédire le retard"):
        prediction_row = data[
            (data["Departure station"] == departure_station) &
            (data["Arrival station"] == arrival_station) &
            (data["Month_Num"] == selected_month_num)
        ]
        if not prediction_row.empty:
            delay = prediction_row.iloc[0]["Predicted delay (min)"]
            minutes = int(delay)
            secondes = int(round((delay - minutes) * 60))
            st.success(f"Retard moyen prévu : **{minutes}min {secondes}s**")
        else:
            st.warning("Aucune donnée disponible pour cette combinaison.")

    st.markdown("---")
    st.header("Évolution mensuelle des retards")

    view_type_month = st.radio("Type de retard à afficher :", ["Retard moyen", "Retard médian"], horizontal=True, key="monthly_delay")

    if view_type_month == "Retard moyen":
        monthly_stats = data.groupby("Month_Num")[["Predicted delay (min)"]].mean().reset_index()
    else:
        monthly_stats = data.groupby("Month_Num")[["Predicted delay (min)"]].median().reset_index()

    fig, ax = plt.subplots(figsize=(10, 5))
    sns.lineplot(data=monthly_stats, x="Month_Num", y="Predicted delay (min)", marker="o", ax=ax)
    ax.set_xticks(range(1, 13))
    ax.set_xticklabels(["Jan", "Fév", "Mar", "Avr", "Mai", "Juin", "Juil", "Aoû", "Sep", "Oct", "Nov", "Déc"])
    ax.set_ylabel("Retard (min)")
    ax.set_xlabel("Mois")
    ax.set_title(view_type_month)
    ax.grid(True)
    st.pyplot(fig)

    st.header("Classement des gares par retard moyen ou médian")

    view_type = st.radio("Afficher les retards selon :", ["Retard moyen", "Retard médian"], horizontal=True)

    if view_type == "Retard moyen":
        delay_stats = data.groupby("Departure station")["Predicted delay (min)"].mean()
    else:
        delay_stats = data.groupby("Departure station")["Predicted delay (min)"].median()

    top_most = delay_stats.sort_values(ascending=False).head(10)
    top_least = delay_stats.sort_values().head(10)
    col1, col2 = st.columns(2)

    with col1:
        fig1, ax1 = plt.subplots(figsize=(8, 6))
        top_most.sort_values().plot(kind="barh", ax=ax1, color="crimson")
        ax1.set_xlabel("Retard (min)")
        ax1.set_title("Plus de retards")
        st.pyplot(fig1)
    with col2:
        fig2, ax2 = plt.subplots(figsize=(8, 6))
        top_least.sort_values(ascending=False).plot(kind="barh", ax=ax2, color="seagreen")
        ax2.set_xlabel("Retard (min)")
        ax2.set_title("Moins de retards")
        st.pyplot(fig2)

    st.markdown("---")
    st.caption("Ici, arriver à l’heure, c’est tellement surfait… et temporellement discutable !")
        

elif page == "Auteur":
    st.title("À propos des auteurs")
    col1, col2, col3 = st.columns(3)
    with col1:
        st.markdown("<div style='text-align: center;'>", unsafe_allow_html=True)
        st.image("image/louis.jpg", width=200, caption="Louis Hector")
        st.markdown("</div>", unsafe_allow_html=True)
    with col2:
        st.markdown("<div style='text-align: center;'>", unsafe_allow_html=True)
        st.image("image/paul.webp", width=200, caption="Paul Ammeloot")
        st.markdown("</div>", unsafe_allow_html=True)
    with col3:
        st.markdown("<div style='text-align: center;'>", unsafe_allow_html=True)
        st.image("image/silas.webp", width=200, caption="Silas Defossez")
        st.markdown("</div>", unsafe_allow_html=True)
    st.markdown("""
    **Objectifs du projet Tardis** :
    - Visualiser les données SNCF sur les retards
    - Comprendre les causes et impacts
    - Proposer une base pour de futures prédictions
    ### Les liens
    - GitHub : (https://github.com/EpitechPGEPromo2029/G-AIA-210-LIL-2-1-tardis-louis.hector)   
    - Epitech :(https://intra.epitech.eu/module/2024/G-AIA-210/LIL-2-1/acti-665896/project/file/G-AIA-210_tardis.pdata)
    """)
    st.markdown("### Technologies utilisées")
    st.markdown("""
    - **Python** 
    - **Pandas** pour le traitement des données  
    - **Streamlit** pour l’interface  
    - **Matplotlib / Seaborn** pour les graphes
    """)
    st.markdown("### Laissez un message")
    feedback = st.text_area("Votre avis / retour sur le projet")
    if st.button("Envoyer le message"):
        st.success("Merci pour votre retour")
    st.markdown("---")
    st.caption("Projet TARDIS de prédiction de retards SNCF — Louis Hector, Paul Ammeloot, Silas Defossez © 2025")
